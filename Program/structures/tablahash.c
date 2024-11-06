#include "tablahash.h"
#include "../words.h"
#include "glist.h"
#include <assert.h>
#include <stdlib.h>

/**
 * Casillas en la que almacenaremos los datos de la tabla hash.
 */
typedef GList HashBox;



HashTable hashtable_make(unsigned size, CopyFunction copy,
                          CompareFunction comp, DestroyFunction destr,
                          HashFunction hash) {

  // Pedimos memoria para la estructura principal y las casillas.
  HashTable table = malloc(sizeof(struct _HashTable));
  assert(table != NULL);
  table->elems = malloc(sizeof(HashBox) * size);
  assert(table->elems != NULL);
  table->numElems = 0;
  table->size = size;
  table->copy = copy;
  table->comp = comp;
  table->destr = destr;
  table->hash = hash;

  // Inicializamos las casillas con datos nulos.
  for (unsigned idx = 0; idx < size; ++idx) {
    table->elems[idx] = glist_make();
  }

  return table;
}


int hashtable_nelems(HashTable table) { return table->numElems; }


int hashtable_size(HashTable table) { return table->size; }


HashBox hashtable_elem(HashTable table, unsigned n) 
{
  if (n >= table->size)
    return NULL;
  else 
    return table->elems[n];
}


void hashtable_destroy(HashTable table) {

  // Destruir cada uno de los datos.
  for (unsigned idx = 0; idx < table->size; ++idx)
    if (!glist_empty(table->elems[idx]))
      glist_destroy(table->elems[idx], table->destr);

  // Liberar el arreglo de casillas y la tabla.
  free(table->elems);
  free(table);
  return;
}


float charge_factor(HashTable table)
{
  return ((float)hashtable_nelems(table) / (float)hashtable_size(table)); 
}
  

void hashtable_insert(HashTable table, void *data) {

  
  // Redimensiono en caso de superar el factor de carga.
  if (charge_factor(table) > CHARGE_FACTOR_MAX)
    hashtable_resize(table);


  // Calculamos la posicion del dato dado, de acuerdo a la funcion hash.
  unsigned idx = table->hash(data) % table->size;

  // Insertar el dato si la casilla estaba libre.
  if (!glist_search(table->elems[idx], data, table->comp)) {
    table->numElems++;
    table->elems[idx] = glist_add_end(table->elems[idx], data, table->copy);
    return;
  }
  //No hacer nada en caso de que el dato este en la casilla.
}


int hashtable_search(HashTable table, void *data) {

  // Calculamos la posicion del dato dado, de acuerdo a la funcion hash.
  unsigned idx = table->hash(data) % table->size;

  // Retornamos 1 o 0 dependiendo de la busqueda(glist_search).
  return glist_search(table->elems[idx], data, table->comp);

}


void hashtable_remove(HashTable table, void *data) {

  // Calculamos la posicion del dato dado, de acuerdo a la funcion hash.
  unsigned idx = table->hash(data) % table->size;

  //Descontar 1 al numero de elementos ya que uno sera eliminado.
  if (glist_remove(table->elems[idx], data, table->comp, table->destr))
    table->numElems--;
  
  //Eliminar el elemento si se encuentra en la table.
  table->elems[idx] = glist_remove(table->elems[idx], data, table->comp, table->destr);
}


void hashtable_resize(HashTable table) {
  
  unsigned newSize = table->size * 2; // Doblamos la capacidad de la tabla.

  GList *newElems = malloc(sizeof(GList) * newSize); // Creamos el nuevo arreglo de listas.
  
  for (unsigned i = 0; i < newSize; i++) // Inicializamos las listas.
    newElems[i] = glist_make();

  unsigned idx = 0;

  for (unsigned i = 0; i < table->size; i++) { // Reinsertamos los valores de la vieja tabla hash
    GList temp = table->elems[i];              // en la nueva tabla hash.
    while (temp != NULL) {
      idx = table->hash(temp->data) % newSize;
      
      if (newElems[idx] == NULL)
        newElems[idx] = temp;
      else
        newElems[idx]->last->next = temp;
      
      newElems[idx]->last = temp;
      temp = temp->next;
      newElems[idx]->last->next = NULL;
    }
  }

  table->size = newSize;
  GList *oldElems = table->elems;
  table->elems = newElems;
  free(oldElems);
}
