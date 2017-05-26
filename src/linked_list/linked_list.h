#ifndef __LINKED_LIST_H__
#define __LINKED_LIST_H__

#include <stdlib.h>
#include <stdbool.h>

typedef struct VariableNode {
  struct VariableNode* next;
  char*  name;
  double value;
  bool   constant;
} VariableNode;

typedef struct LinkedList {
  VariableNode* head;
  size_t size;
} LinkedList;

LinkedList*   linkedListCreate();
VariableNode* linkedListGet(LinkedList* list, char* str);

bool linkedListContainsValue(LinkedList* list, char* str);
void linkedListDestroy(LinkedList* list);
void linkedListPut(LinkedList* list, char* str, double value, bool constant);
void linkedListPrint(LinkedList* list);

#endif /* end of include guard: __LINKED_LIST_H__ */
