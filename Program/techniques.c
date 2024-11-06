#include "mainfunctions.h"
#include "techniques.h"
#include "words.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEN_ALPHABET 26

char *alphabet() { return "abcdefghijklmnopqrstuvwxyz"; }

int swapping_technique(Word *w, HashTable dTable, HashTable *distTables,
                       WList *suggestions, int *lenS, int dist, int cd)
{
  int len = w->len;
  char *word = w->word;

  for (int i = 0; i < len - 1; i++) { // Recorremos la palabra inicial.

    swap_letters(word, i, i + 1);                                   // Intercambiamos los caracteres en la pos i e i+1 de [ word ].
    check_word(dTable, distTables, w, suggestions, lenS, dist, cd); // Analizamos la palabra obtenida y verificamos si se encuentra en el diccionario.

    if (*lenS == SUGGESTIONS_MAX) { // Cortamos el bucle si completamos la cantidad de sugerencias establecida.
      swap_letters(word, i, i + 1); // Reconstruimos la palabra inicial.
      return 1;
    }

    swap_letters(word, i, i + 1); // Reconstruimos la palabra inicial.
  }

  return 0;
}

int replacing_technique(Word *w, HashTable dTable, HashTable *distTables,
                        WList *suggestions, int *lenS, int dist, int cd)
{
  char *word = w->word;
  int len = w->len;

  char *alph = alphabet(), c = 0;

  for (int i = 0; i < len; i++) { // Recorremos la palabra inicial.

    c = word[i];

    for (int j = 0; j < LEN_ALPHABET; j++) { // Recorremos el alfabeto.

      if (alph[j] != c) {

        word[i] = alph[j]; // Cambiamos el caracter en i por cada letra del alfabeto menos de la inicial.

        check_word(dTable, distTables, w, suggestions, lenS, dist, cd); // Analizamos la palabra obtenida y verificamos si se encuentra en el diccionario.

        if (*lenS == SUGGESTIONS_MAX) {  // Cortamos el bucle si completamos la cantidad de sugerencias establecida.
          word[i] = c; // Reconstruimos la palabra inicial.
          return 1;
        }
      }
    }

    word[i] = c; // Reconstruimos la palabra inicial.
  }
  return 0;
}

int removing_technique(Word *w, HashTable dTable, HashTable *distTables,
                       WList *suggestions, int *lenS, int dist, int cd)
{

  if (w->len > 1) {

    int len = w->len;
    Word *buff = malloc(sizeof(Word));
    buff->word = malloc(len + 1);
    buff->word[len - 1] = 0;
    buff->len = len - 1;

    for (int i = 0; i < len; i++) { // Recorremos la palabra inicial.

      for (int j = 0, k = 0; j < len; k++) { // Recorremos la palabra inicial
                                             // y copiamos sobre [ buff ] la
        if (k != i) {                        // palabra [ word ] menos el
          (buff->word)[j] = (w->word)[k];    // caracter word[i].
          j++;
        }
      }

      check_word(dTable, distTables, buff, suggestions, lenS, dist, cd); // Analizamos la palabra obtenida y verificamos si se encuentra en el diccionario.

      if (*lenS == SUGGESTIONS_MAX) { // Cortamos el bucle si completamos la cantidad de sugerencias establecida.
        free(buff->word);
        free(buff);
        return 1;
      }

      add_letter(buff->word, len, i, w->word[i]); // Reconstruimos la palabra inicial.
    }

    word_destroy(buff);
  }
  return 0;
}

int insertion_technique(Word *w, HashTable dTable, HashTable *distTables,
                        WList *suggestions, int *lenS, int dist, int cd)
{
  int len = w->len;
  Word *buff = malloc(sizeof(Word));
  buff->word = malloc(len + 2);
  buff->word[len + 1] = 0;
  buff->len = len + 1;

  char *alph = alphabet();

  memcpy(&(buff->word[1]), w->word, len + 1); // Dejo un lugar en buff[0].

  for (int i = 0; i <= len; i++) { // Recorremos la palabra inicial.

    for (int j = 0; j < LEN_ALPHABET; j++) { // Recorremos el alfabeto.

      buff->word[i] = alph[j]; // Insertamos cada caracter del alfabeto sobre buff[i].

      check_word(dTable, distTables, buff, suggestions, lenS, dist, cd); // Analizamos la palabra obtenida y verificamos si se encuentra en el diccionario.

      if (*lenS == SUGGESTIONS_MAX) { // Cortamos el bucle si completamos la cantidad de sugerencias establecida.
        word_destroy(buff);
        return 1;
      }
    }

    buff->word[i] = buff->word[i + 1]; // Dejamos un lugar en la siguiente posicion.
  }
  word_destroy(buff);
  return 0;
}

int splitting_technique(Word *w, HashTable dTable, WList *suggestions, int *lenS)
{

  int len = w->len;
  if (len > 1) {
    Word *buff = malloc(sizeof(Word)), *word1 = malloc(sizeof(Word)), *word2 = malloc(sizeof(Word));
    buff->word = malloc(len + 2);
    word1->word = malloc(len);
    word2->word = malloc(len);

    buff->word[len + 1] = 0;
    buff->word = memcpy(buff->word, w->word, len + 1);
    buff->len = len + 1;

    for (int i = 1; i < len; i++) {
      word1->len = i;
      word2->len = len - word1->len;
      split_words(w->word, len, i, word1->word, word2->word); // Copiamos sobre [ word1 ] y sobre [ word2 ] cada parte de la palabra dividida en la pos i.

      if (hashtable_search(dTable, word1) && hashtable_search(dTable, word2)) { // Si ambas palabras se encuentran en el diccionario.

        add_letter(buff->word, buff->len, i, ' '); // Agrego un ' ' en buff[i] y luego lo agrego a sugerencias.

        if (!glist_search(*suggestions, buff, (ComparatorFunction)word_compare)) {
          *suggestions = glist_add_end(*suggestions, buff, (CopierFunction)word_copy);
          (*lenS)++;
        }

        if (*lenS == SUGGESTIONS_MAX) { // Cortamos el bucle si completamos la cantidad de sugerencias establecida.
          word_destroy(buff);
          word_destroy(word1);
          word_destroy(word2);
          return 1;
        }
      }
    }

    word_destroy(buff);
    word_destroy(word1);
    word_destroy(word2);
  }
  return 0;
}

void add_letter(char *s, int len, int i, char letter)
{
  for (int j = len; j > i; j--)
    s[j] = s[j - 1];
  s[i] = letter;
}

void remove_letter(char *buff, int i)
{

  for (int j = i; buff[j] != '\0'; j++)
    buff[j] = buff[j + 1]; // Remuevo una letra en la posicion i.
}

void swap_letters(char *buff, int i1, int i2)
{
  char c = buff[i2];
  buff[i2] = buff[i1];
  buff[i1] = c;
}

void split_words(char *buff, int len, int i, char *word1, char *word2)
{
  char c;
  c = buff[i];

  int len1 = i;
  int len2 = len - i;

  memcpy(word2, &buff[i], len2 + 1); // Copio en [word2] la palabra inicial desde la posicion i.
  buff[i] = 0;
  memcpy(word1, buff, len1 + 1); // Copio en [word1] la palabra inicial hasta la posicion i(sin incluir).
  buff[i] = c;
}