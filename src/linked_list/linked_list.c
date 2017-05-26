#include "linked_list.h"
#include <stdio.h>
#include <string.h>

void  nodeDestroyRecursive(VariableNode* node);
bool  nodeContainsRecursive(VariableNode* node, char* str);
void  nodePrint(VariableNode* node);
VariableNode* nodeGetLast(VariableNode* node);
VariableNode* nodeFindRecursive(VariableNode* node, char* str);
VariableNode* nodeCreate(char* str, double value, bool constant);

LinkedList* linkedListCreate() {
  LinkedList* list = (LinkedList*) malloc(sizeof(LinkedList));
  list->size = 0;
  list->head = NULL;

  return list;
}

void linkedListDestroy(LinkedList* list) {
  nodeDestroyRecursive(list->head);

  free(list);
  list = NULL;
}

void linkedListPut(LinkedList* list, char* str, double value, bool constant) {
  VariableNode* last    = nodeGetLast(list->head);
  VariableNode* newVariableNode = nodeCreate(str, value, constant);

  if(last == NULL) {
    list->head = newVariableNode;
  } else {
    last->next = newVariableNode;
  }

  ++list->size;
}

bool linkedListContainsValue(LinkedList* list, char* str) {
  return linkedListGet(list, str) == NULL ? false : true;
}

VariableNode* linkedListGet(LinkedList* list, char* str) {
  return nodeFindRecursive(list->head, str);
}

void linkedListPrint(LinkedList* list) {
  printf("LinkedList [");
  nodePrint(list->head);
  printf("]\n");
}

void nodePrint(VariableNode* node) {
  if(node == NULL) { return; }

  printf("{%s -> %lf | %s}", node->name, node->value, node->constant ? "true" : "false");
  if(node->next != NULL) {
    printf(", ");
  }

  nodePrint(node->next);
}

VariableNode* nodeCreate(char* str, double value, bool constant) {
    VariableNode* node = (VariableNode*) malloc(sizeof(VariableNode));
    node->name = (char*) malloc(sizeof(char) * (strlen(str) + 1));
    strcpy(node->name, str);
    node->value    = value;
    node->next     = NULL;
    node->constant = constant;
    return node;
}

VariableNode* nodeGetLast(VariableNode* node) {
  if(node       == NULL) { return NULL; }
  if(node->next == NULL) { return node; }

  return nodeGetLast(node->next);
}

void nodeDestroyRecursive(VariableNode* node) {
  if(node == NULL) { return; }

  nodeDestroyRecursive(node->next);
  free(node->name);
  node->name = NULL;
  free(node);
  node = NULL;
}

VariableNode* nodeFindRecursive(VariableNode* node, char* str) {
  if(node == NULL) { return NULL; }

  return strcmp(str, node->name) == 0 ? node
                                      : nodeFindRecursive(node->next, str);
}
