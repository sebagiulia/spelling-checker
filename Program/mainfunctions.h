#ifndef __MAIN_FUNCTIONS_H_
#define __MAIN_FUNCTIONS_H_

#include "structures/tablahash.h"
#include "structures/glist.h"
#include "words.h"
#include <stdio.h>

#define SUGGESTIONS_MAX 5

typedef GList WList;

/*
 * Imprime en un archivo [ file ] el listado de sugerencias para una palabra. 
 */
void show_suggestions(HashTable dTable, Word *w, int line, FILE *file, int cd);

/*
 * Devuelve una lista de sugerencias para una palabra dada.
 * En primer lugar, crea un arreglo de tablas hash de acuerdo a cada distancia,
 * Luego las va rellenando a medida que recorre cada una de las distancias. Si 
 * previamente no se llego al limite de sugerencias, la funcion prueba con todas
 * las palabras posibles hasta una distancia maxima de la palabra original [ word ]
 * y retorna las que pudo recolectar.
 */
WList create_suggetions(HashTable dTable, Word *w, int cd);

/*
 * Inserta sobre una tabla de distancia [ dist ] todas las palabras que se encuentren  
 * a una distancia [ dist ] de la palabra original sin contar las repetidas en distancias
 * menores y en si misma.
 * Esto lo hace recorriendo y procesando cada palabra de la tabla de distancia [ dist - 1].
 * Si la función logra completar la lista de sugerencias termina retornando 1.
 */
int make_wordsList(HashTable dtable, HashTable *tables, WList *suggestions, int *lenS, int dist, int cd);

/*
 * Para una palabra [ word ] se le aplican diferentes tecnicas(intercambios, reemplazos, eliminacion,
 * insercion y division) para encontrar sugerencias para dicha palabra. Cada palabra surgida a partir
 * de una tecnica se la inserta en su tabla de distancia[ dist ] correspondiente y en una lista de
 * sugerencias si es que se encontraba en el diccionario correspondiente.
 * Si la función logra completar la lista de sugerencias termina retornando 1.
 */
int process_word(HashTable dTable, HashTable *tables, Word *w, WList *suggestions, int *lenS, int dist, int cd);

/*
 * Para una palabra [ word ], se verifica que no se encuentre en alguna de las tablas de distancias menores
 * o iguales a [ dist ]. Si no se encuentra, se busca en el diccionario correspondiente y se la agrega a la
 * lista de sugerencias si es que esta en este. Si no lo esta, se la inserta igualmente en la tabla de su
 * distancia correspondiente. Si ya se encontraba en alguna de las tablas la funcion termina.
 */
void check_word(HashTable dtable, HashTable *tables, Word *w, WList *suggestions, int *lenS, int dist, int cd);


/*
 * Busca en un arreglo de tablas hash un determinado string [ word ].
 * Si se encuentra retorna 1, sino, 0.
 */
int search_in_tables(HashTable *tables, int n, Word *w);

#endif


