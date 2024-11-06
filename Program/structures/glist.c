#include "glist.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

GList glist_make() { return NULL; }

void glist_destroy(GList list, DestroyerFunction destroy)
{
  GNode *nodeToDelete;
  while (list != NULL) {
    nodeToDelete = list;
    list = list->next;
    destroy(nodeToDelete->data);
    free(nodeToDelete);
  }
}

int glist_empty(GList list) { return (list == NULL); }

int glist_len(GList list)
{
  if (glist_empty(list))
    return 0;
  int counter = 0;
  for (GList temp = list; temp != NULL; temp = temp->next, counter++);
  return counter;
}

int glist_search(GList list, void *data, ComparatorFunction comp)
{

  if (glist_empty(list))
    return 0;

  GList temp = list;
  for (; temp != NULL; temp = temp->next) {
    if (comp(temp->data, data) == 0)
      return 1;
  }

  return 0;
}

GList glist_remove(GList list, void *data, ComparatorFunction comp, DestroyerFunction destroy)
{
  if (glist_empty(list))
    return list;
  GList temp = list;
  if (comp(temp->data, data) == 0) {
    GList aux = temp->next;
    destroy(temp->data);
    free(temp);
    return aux;
  }

  for (; temp != NULL; temp = temp->next) {
    if (comp(temp->next->data, data))
    {
      GList aux = temp->next->next;
      destroy(temp->next->data);
      free(temp->next);
      temp->next = aux;
      return list;
    }
  }
  return list;
}

GList glist_add_start(GList list, void *data, CopierFunction copy)
{
  GNode *newNode = malloc(sizeof(GNode));
  assert(newNode != NULL);
  newNode->next = list;
  newNode->data = copy(data);
  return newNode;
}

GList glist_add_end(GList list, void *data, CopierFunction copiar)
{
  GNode *newNode = malloc(sizeof(GNode));
  assert(newNode != NULL);
  newNode->next = NULL;
  newNode->data = copiar(data);

  if (glist_empty(list)) {
    newNode->last = newNode;
    return newNode;
  }
  list->last->next = newNode;
  list->last = newNode;
  return list;
}

void glist_traverse(GList list, VisiterFunction visit)
{
  for (GNode *node = list; node != NULL; node = node->next)
    visit(node->data);
}

GList glist_filtrar(GList list, CopierFunction c, Predicate p)
{
  GList listFiltrada = glist_make();
  GNode *nodeTemp = list;
  while (!glist_empty(nodeTemp)) {
    if (p(nodeTemp->data))
      listFiltrada = glist_add_start(listFiltrada, nodeTemp->data, c);
    nodeTemp = nodeTemp->next;
  }
  return listFiltrada;
}

GList glist_concatenate(GList list1, GList list2)
{
  if (glist_empty(list1))
    return list2;
  if (glist_empty(list2))
    return list1;

  list1->last->next = list2;
  list1->last = list2->last;

  return list1;
}