#ifndef __GLIST_H__
#define __GLIST_H__

typedef int (*ComparatorFunction) (void *data, void *data2);
typedef void (*DestroyerFunction)(void *data);
typedef void *(*CopierFunction)(void *data);
typedef void (*VisiterFunction)(void *data);
typedef int (*Predicate)(void *data);


typedef struct _GNode {
  void *data;
  struct _GNode *next, *last;
} GNode;

typedef GNode *GList;


/**
 * Devuelve una lista vacía.
 */
GList glist_make();


/**
 * Destruccion de la lista.
 */
void glist_destroy(GList list, DestroyerFunction destroy);


/**
 * Determina si la lista es vacía.
 */
int glist_empty(GList list);


/**
 * Determina el largo de la lista.
 */
int glist_len(GList list);


/**
 * Retorna 1 si el elemento se encuentra en la lista o 0 en caso contrario.
 */
int glist_search(GList list, void *data,  ComparatorFunction comp);


/**
 * Si el elemento dado se encuentra en la lista es eliminado, sino, no hace nada.
 */
GList glist_remove(GList list, void *data, ComparatorFunction comp, DestroyerFunction destroy);


/**
 * Agrega un elemento al inicio de la lista.
 */
GList glist_add_start(GList list, void *data, CopierFunction copiar);


/**
 * Agrega un elemento al final de la lista.
 */
GList glist_add_end(GList list, void *data, CopierFunction copiar);


/**
 * Recorrido de la lista, utilizando la funcion pasada.
 */
void glist_traverse(GList list, VisiterFunction visit);

/**
 * Conecta la lista1 con la lista 2.
 */
GList glist_concatenate(GList list1, GList list2);

#endif /* __GLIST_H__ */


