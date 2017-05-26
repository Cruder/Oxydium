#ifndef __LINKED_LIST_H__
#define __LINKED_LIST_H__

#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
  struct Node* next;
  char*  name;
  double value;
  bool   constant;
} Node;

typedef struct LinkedList {
  Node* head;
  size_t size;
} LinkedList;

LinkedList* linkedListCreate();
void        linkedListDestroy(LinkedList* list);

bool        linkedListContainsValue(LinkedList* list, char* str);
void        linkedListPut(LinkedList* list, char* str, double value,
                          bool constant);
Node*       linkedListGet(LinkedList* list, char* str);

void        linkedListPrint(LinkedList* list);

#endif /* end of include guard: __LINKED_LIST_H__ */
