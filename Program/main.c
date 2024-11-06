#include "structures/tablahash.h"
#include "filefunctions.h"
#include "words.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define INITIAL_SIZE 1000
#define MAX_LEN_WORD 50

int main(int argc, char *argv[])
{

  if (argc != 3 && argc != 4) { // Parametros incorrectos.

    printf("File input error.\n");
    return 0;

  } else {  

    int cd = (argc == 4 && strcmp("-cd", argv[3]) == 0);           // Chequeo de duplicados (Check Duplicates) activo (1) o inactivo (0).
    char *intPath = argv[1];
    char *outPath = argv[2];

	  // Inicializar tabla hash de diccionario.
    HashTable dTable = hashtable_make(INITIAL_SIZE,
                                  (CopyFunction) word_copy,
                                  (CompareFunction) word_compare,
                                  (DestroyFunction) word_destroy,
                                  (HashFunction) word_hash);

	  // Cargar diccionario sobre [ dTable ].
    char dictionary[MAX_LEN_WORD + 4];
    printf("Enter dictionary file: ");
    scanf ("%s", dictionary);
	  int dictionaryLen = load_dictionary(dictionary, dTable);

    //Correccion de texto.
    correction_text(intPath, outPath, dTable, cd);

    //Destruccion de tabla hash diccionario.
    hashtable_destroy(dTable);

	  return 0;

  }
}