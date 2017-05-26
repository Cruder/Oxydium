#include "linked_list.h"
#include <stdio.h>
#include <string.h>

Node* nodeGetLast(Node* node);
void  nodeDestroyRecursive(Node* node);
bool  nodeContainsRecursive(Node* node, char* str);
Node* nodeFindRecursive(Node* node, char* str);
Node* nodeCreate(char* str, double value, bool constant);
void nodePrint(Node* node);

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
  Node* last    = nodeGetLast(list->head);
  Node* newNode = nodeCreate(str, value, constant);

  if(last == NULL) {
    list->head = newNode;
  } else {
    last->next = newNode;
  }

  ++list->size;
}

bool linkedListContainsValue(LinkedList* list, char* str) {
  return linkedListGet(list, str) == NULL ? false : true;
}

Node* linkedListGet(LinkedList* list, char* str) {
  return nodeFindRecursive(list->head, str);
}

void linkedListPrint(LinkedList* list) {
  printf("LinkedList [");
  nodePrint(list->head);
  printf("]\n");
}

void nodePrint(Node* node) {
  if(node == NULL) { return; }

  printf("{%s -> %lf | %s}", node->name, node->value, node->constant ? "true" : "false");
  if(node->next != NULL) {
    printf(", ");
  }

  nodePrint(node->next);
}

Node* nodeCreate(char* str, double value, bool constant) {
    Node* node = (Node*) malloc(sizeof(Node));
    node->name = (char*) malloc(sizeof(char) * (strlen(str) + 1));
    strcpy(node->name, str);
    node->value    = value;
    node->next     = NULL;
    node->constant = constant;
    return node;
}

Node* nodeGetLast(Node* node) {
  if(node       == NULL) { return NULL; }
  if(node->next == NULL) { return node; }

  return nodeGetLast(node->next);
}

void nodeDestroyRecursive(Node* node) {
  if(node == NULL) { return; }

  nodeDestroyRecursive(node->next);
  free(node->name);
  node->name = NULL;
  free(node);
  node = NULL;
}

Node* nodeFindRecursive(Node* node, char* str) {
  if(node == NULL) { return NULL; }

  return strcmp(str, node->name) == 0 ? node
                                      : nodeFindRecursive(node->next, str);
}
