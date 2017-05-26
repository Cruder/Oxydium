#ifndef __VARIABLE_TABLE_H__
#define __VARIABLE_TABLE_H__

#include "hashmap/hashmap.h"

typedef struct HashNode {
  struct HashNode* next;
  struct HashNode* previous;
  Hashmap* map;
} HashNode;

typedef struct VariableTable {
  HashNode* head;
  size_t depth;
} VariableTable;

VariableTable* variableTableCreate();
void           variableTableDestroy(VariableTable* table);

void           variableTableIncrementDepth(VariableTable* table);
void           variableTableDecrementDepth(VariableTable* table);

Node*          variableTableGetVariable(VariableTable* table, char* str);
void           variableTableSetVariable(VariableTable* table, char* str,
                                        double value, bool constant);
void           variableTableDisplay(VariableTable* table);
void           variableTableUpdateVariable(Node* node, double value);

#endif /* end of include guard: __VARIABLE_TABLE_H__ */
