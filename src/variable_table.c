#include "variable_table.h"
#include <stdio.h>

HashNode* hashNodeCreate();
void      hashNodeDestroy(HashNode* node);
HashNode* hashNodeGetLast(HashNode* node);

VariableTable* variableTableCreate() {
  VariableTable* table = (VariableTable*) malloc(sizeof(VariableTable));
  table->head  = hashNodeCreate();
  table->depth = 1;

  return table;
}

void variableTableDestroy(VariableTable* table) {
  table->depth = 0;
  hashNodeDestroy(table->head);

  free(table);
  table = NULL;
}

void variableTableIncrementDepth(VariableTable* table) {
  HashNode* previous = hashNodeGetLast(table->head);
  HashNode* next     = hashNodeCreate();

  previous->next = next;
  next->previous = previous;

  ++table->depth;
}

void variableTableDecrementDepth(VariableTable* table) {
  if(table->depth == 1) { return; }

  HashNode* node = hashNodeGetLast(table->head)->previous;
  hashNodeDestroy(node->next);
  node->next = NULL;

  --table->depth;
}

Node* variableTableGetVariable(VariableTable* table, char* str) {
  HashNode* current = hashNodeGetLast(table->head);

  do {
    Node* result = hashmapGet(current->map, str);
    if(result) { return result; }

    current = current->previous;
  } while(current != NULL);

  return NULL;
}

void variableTableSetVariable(VariableTable* table, char* str, double value) {
  HashNode* hashNode = hashNodeGetLast(table->head);

  hashmapPut(hashNode->map, str, value);
}

void variableTableDisplay(VariableTable* table) {
  printf("VariableTable []\n");
}

HashNode* hashNodeCreate() {
  HashNode* node = (HashNode*) malloc(sizeof(HashNode));
  node->map  = hashmapCreate();
  node->next = NULL;
  node->previous = NULL;

  return node;
}

void hashNodeDestroy(HashNode* node) {
  if(node == NULL) { return; }

  hashNodeDestroy(node->next);
  hashmapDestroy(node->map);

  free(node);
  node = NULL;
}

HashNode* hashNodeGetLast(HashNode* node) {
  if(node       == NULL) { return NULL; }
  if(node->next == NULL) { return node; }

  return hashNodeGetLast(node->next);
}
