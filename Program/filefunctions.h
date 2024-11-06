#ifndef __FILE_H_
#define __FILE_H_

#include "structures/tablahash.h"

/*
 * Lee un archivo diccionario e inserta cada palabra sobre una tabla hash.
 * Retorna la cantidad de palabras en el diccionario.
 */
int load_dictionary(const char *path, HashTable dTable);


/*
 * Lee un archivo de entrada A y uno de salida B, lee cada palabra del
 * archivo A y verifica si se encuentran en un diccionario. Si no se 
 * encuentran, se imprime sobre el archivo B una lista de sugerencias.
 */
void correction_text(char *intPath, char *outPath, HashTable dTable, int cd);




#endif