#include "mainfunctions.h"
#include "techniques.h"
#include <stdlib.h>
#include <string.h>

#define MAX_DIST 3

void show_suggestions(HashTable dTable, Word *w, int line, FILE *file, int cd)
{

  WList suggestions = create_suggetions(dTable, w, cd); // Creamos la lista de sugerencias [ suggestions ].

  fprintf(file, "Linea %d, '%s' no esta en el diccionario.\n", line, w->word);

  if (glist_empty(suggestions)) { // Si no se encontraron sugerencias.
    fprintf(file, "No se encontraron sugerencias.\n\n");
    return;
  }

  fprintf(file, "Quizas quiso decir:");

  Word *word = malloc(sizeof(Word));
  for (WList temp = suggestions; temp != NULL; temp = temp->next) { // Recorremos la lista de sugerencias.
    word = word_copy(temp->data);
    if (temp->next != NULL)
      fprintf(file, " %s,", word->word);
    else
      fprintf(file, " %s.", word->word);
    free(word->word);
  }

  fprintf(file, "\n\n");

  free(word);
  glist_destroy(suggestions, (DestroyerFunction)word_destroy);
}

WList create_suggetions(HashTable dTable, Word *w, int cd)
{

  WList suggestions = glist_make(); // Inicializamos la lista de sugerencias.
  int lenS = 0;                     // Largo de la lista [ suggestions ].

  HashTable *distTables = malloc(sizeof(HashTable) * MAX_DIST); // Creamos las tablas de cada distancia menos la ultima, incluida la distancia 0.

  for (int i = 1; i < MAX_DIST; i++) { // Inicializamos las tablas de cada distancia.
    distTables[i] = hashtable_make(100, (CopierFunction)word_copy,
                                   (ComparatorFunction)word_compare,
                                   (DestroyerFunction)word_destroy,
                                   (HashFunction)word_hash);
  }

  distTables[0] = hashtable_make(2, (CopierFunction)word_copy,     // Inicializamos la tabla de distancia 0
                                 (ComparatorFunction)word_compare, // La cual tendra unicamente un elemento.
                                 (DestroyerFunction)word_destroy,  // (El elemento original).
                                 (HashFunction)word_hash);
  hashtable_insert(distTables[0], w); // Insertamos la palabra a corregir en [ distTables[0] ].

  for (int i = 0; i < MAX_DIST; i++) { // Recorremos cada una de las distancias.

    if (make_wordsList(dTable, distTables, &suggestions, &lenS, i, cd)) { // Armamos las tablas para cada distancia.

      // Retornamos si completamos la cantidad de sugerencias maxima.
      for (int i = 0; i < MAX_DIST; i++)
        hashtable_destroy(distTables[i]);
      free(distTables);
      return suggestions;
    }
  }

  // En este punto no se pudo completar la lista de sugerencias, por lo que se retorna hasta donde se haya llegado.
  for (int i = 0; i < MAX_DIST; i++)
    hashtable_destroy(distTables[i]);
  free(distTables);
  return suggestions;
}

int make_wordsList(HashTable dTable, HashTable *distTables, WList *suggestions, int *lenS, int dist, int cd)
{
  int cap = hashtable_size(distTables[dist]); // Capacidad de [ distTables[dist] ].

  for (int i = 0; i < cap; i++) { // Recorremos toda la tabla [ distTables[dist] ].

    for (HashBox temp = hashtable_elem(distTables[dist], i); temp != NULL; temp = temp->next) {    // Recorremos cada lista de la tabla.
      if (process_word(dTable, distTables, temp->data, suggestions, lenS, dist, cd)) // Procesamos cada palabra de cada lista de la tabla.
        return 1;                                                                    // Retornamos si completamos la cantidad de sugerencias maximas.
    }
  }
  return 0;
}

int process_word(HashTable dTable, HashTable *distTables, Word *w, WList *suggestions, int *lenS, int dist, int cd)
{

  Word *buff = word_copy(w);

  //// TECHNIQUE ONE ////
  if (swapping_technique(buff, dTable, distTables, suggestions, lenS, dist, cd)) {    // Aplicamos tecnica de intercambios
    word_destroy(buff); // y retornamos si completamos sugerencias.
    return 1;
  }

  //// TECHNIQUE TWO ////
  if (replacing_technique(buff, dTable, distTables, suggestions, lenS, dist, cd)) {   // Aplicamos tecnica de reemplazos
    word_destroy(buff); // y retornamos si completamos sugerencias.
    return 1;
  }

  //// TECHNIQUE THREE ////
  if (removing_technique(buff, dTable, distTables, suggestions, lenS, dist, cd)) {    // Aplicamos tecnica de eliminacion y
    word_destroy(buff); // retornamos si completamos sugerencias.
    return 1;
  }

  //// TECHNIQUE FOUR ////
  if (insertion_technique(buff, dTable, distTables, suggestions, lenS, dist, cd)) {  // Aplicamos tecnica de insercion y
    word_destroy(buff); // retornamos si completamos sugerencias.
    return 1;
  }

  //// TECHNIQUE FIVE ////
  if (splitting_technique(buff, dTable, suggestions, lenS)) {   // Aplicamos tecnica de division y
    word_destroy(buff); // retornamos si completamos sugerencias.
    return 1;
  }

  word_destroy(buff);
  return 0;
}

void check_word(HashTable dTable, HashTable *distTables, Word *w, WList *suggestions, int *lenS, int dist, int cd)
{
  int c = 1;
  if (cd) // Si corrimos el programa con chequeo de duplicados.
    c = !search_in_tables(distTables, dist + 1, w);

  if (c) { // Filtramos las posibles palabras repetidas obtenidas en las distancias anteriores y en la actual.

    if (hashtable_search(dTable, w)) { // Si la palabra se encuentra en el diccionario.

      if (!glist_search(*suggestions, w, (ComparatorFunction)word_compare)) { // Si no se encontraba en la lista de sugerencias.
        *suggestions = glist_add_end(*suggestions, w, (CopierFunction)word_copy); // Agregamos la palabra a la lista de sugerencias.
        (*lenS)++;
      }
    }

    if (dist + 1 != MAX_DIST) // Insertamos la palabra en la nueva lista de distancias.
      hashtable_insert(distTables[dist + 1], w);
  }
}

int search_in_tables(HashTable *tables, int n, Word *w)
{

  for (int i = 0; i <= n && i < MAX_DIST; i++) { // Recorremos el arreglo de tablas y buscamos el elemento [ w ].
    if (hashtable_search(tables[i], w))
      return 1;
  }
  return 0;
}