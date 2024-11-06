#include "filefunctions.h"
#include "mainfunctions.h"
#include "words.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define MAX_LEN_WORD 50

int load_dictionary(const char *path, HashTable dTable)
{

  int sz = MAX_LEN_WORD;
  char word[sz];

  FILE *file = fopen(path, "rb"); // Abrimos el archivo del diccionario sobre [ file ].

  int i = 0;

  if (file == NULL) { // Si ocurre un error al abril el archivo.
    perror("readfile.fopen");
    exit(1);
  }

  Word *w = malloc(sizeof(Word));

  while (feof(file) == 0) { // Recorremos el archivo del diccionario.

    fscanf(file, "%s", word); // Leemos cada subcadena hasta encontrar un '\n' y lo almacenamos sobre [ word ].
    w->len = strlen(word);
    w->word = word;

    hashtable_insert(dTable, w); // Insertamos [ w ] sobre la tabla hash.
    i++;
  }

  free(w);
  fclose(file);

  return i; // Retornamos la longitud del diccionario.
}

void correction_text(char *intPath, char *outPath, HashTable dTable, int cd)
{

  int line = 1, i = 0, mistakes = 0;

  FILE *intFile = fopen(intPath, "rb"); // Abrimos el archivo del texto a corregir sobre [ intFile ].
  assert(intFile != NULL);
  FILE *outFile = fopen(outPath, "w"); // Abrimos el archivo del diccionario sobre [ outFile ].
  assert(outFile != NULL);

  char *word = malloc(MAX_LEN_WORD);
  Word *w = malloc(sizeof(Word));
  w->word = word; // Almacenamos sobre [ w ] todas las variaciones de [ word ].

  char c = 0;
  while (feof(intFile) == 0) { // Recorremos caracter por caracter.

    c = fgetc(intFile); // Almacenamos sobre [ c ] el caracter leido.

    if (!invalid_character(c)) { // Caracter valido

      word[i] = tolower(c); // Almacenamos en la posicion i de la cadena [ word ] el caracter [ c ] en su forma minuscula.
      i++;
    } else { // Caracter invalido

      if (i == 0 || invalid_character(word[i - 1])) // Si el caracter invalido aparece al principio.
        i = 0;                                      // o aparece mas de una vez seguida es ignorado.

      else { // Caracter invalido posterior a caracter valido.

        word[i] = 0; // Agregamos terminador a la cadena [ word ].
        w->len = i;

        if (!hashtable_search(dTable, w)) { // Verificamos si [ word ] esta en el diccionario.
          // Si no lo esta...
          printf("Procesando [ %s ]\n", word);
          show_suggestions(dTable, w, line, outFile, cd); // Mostramos sugerencias en caso de que existan.
          mistakes++;
        }

        i = 0; // Reiniciamos la posicion i.
      }

      if (c == '\n') // Contamos cada salto de linea.
        line++;
    }
  }

  printf("\n%d errores encontrados.\n", mistakes);
  printf("Archivo escrito -> %s\n", outPath);

  word_destroy(w);

  fclose(outFile);
  fclose(intFile);
}