#ifndef __HASHTABLE_H__
#define __HASHTABLE_H__
#include "glist.h"

#define CHARGE_FACTOR_MAX 0.7F


/**
 * Casillas en la que almacenaremos los datos de la tabla hash.
 */
typedef GList HashBox;


typedef void *(*CopyFunction)(void *data);
/** Retorna una copia fisica del dato */
typedef int (*CompareFunction)(void *data1, void *data2);
/** Retorna un entero negativo si dato1 < dato2, 0 si son iguales y un entero
 * positivo si dato1 > dato2  */
typedef void (*DestroyFunction)(void *data);
/** Libera la memoria alocada para el dato */
typedef unsigned (*HashFunction)(void *data);
/** Retorna un entero sin signo para el dato */


/**
 * Estructura principal que representa la tabla hash.
 */
struct _HashTable {
  HashBox *elems;
  unsigned numElems;
  unsigned size;
  CopyFunction copy;
  CompareFunction comp;
  DestroyFunction destr;
  HashFunction hash;
};

typedef struct _HashTable *HashTable;

/**
 * Crea una nueva tabla hash vacia, con la capacidad dada.
 */
HashTable hashtable_make(unsigned size, CopyFunction copy,
                          CompareFunction comp, DestroyFunction destr,
                          HashFunction hash);

/**
 * Retorna el numero de elementos de la tabla.
 */
int hashtable_nelems(HashTable table);

/**
 * Retorna la capacidad de la tabla.
 */
int hashtable_size(HashTable table);

/**
 * Retorna la casilla de la posicion n.
 */
HashBox hashtable_elem(HashTable table, unsigned n);

/**
 * Destruye la tabla.
 */
void hashtable_destroy(HashTable table);

/**
 * Retorna el factor de carga de la tabla.
 */
float charge_factor(HashTable table);

/**
 * Inserta un dato en la tabla, o lo reemplaza si ya se encontraba.
 */
void hashtable_insert(HashTable table, void *data);

/**
 * Retorna 1 si un dato en la tabla coincide con el dato dado, o 0 si el dato
 * buscado no se encuentra en la tabla.
 */
int hashtable_search(HashTable table, void *data);

/**
 * Elimina el dato de la tabla que coincida con el dato dado.
 */
void hashtable_remove(HashTable table, void *data);

/**
 * Duplica la size de la tabla y reposiciona todos los elementos de acuerdo a la nueva
 * posicion que le asigna la funcion de hash.
 */
void hashtable_resize(HashTable table);

#endif /* __HASHTABLE_H__ */