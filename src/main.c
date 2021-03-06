#include "variable_table.h"
#include <stdio.h>
#include <assert.h>

// val nomnomnom = 21.4
// print(nomnomnom) # 21.4
// do
//   var nomnomnom = 5.1
//   print(nomnomnom) # 5.1
//
//   var rm = 7.1
//   print(rm) # 7.1
// end
// print(rm) # Error
// print(nomnomnom) # 21.4
int main(int argc, char const *argv[]) {
  VariableTable* table = variableTableCreate();
  VariableNode* node = NULL;

  variableTableSetVariable(table, "nomnomnom", 21.4, true);
  node = variableTableGetVariable(table, "nomnomnom");
  variableTableUpdateVariable(node, 12);
  printf("{%s -> %lf}\n", node->name, node->value);
  variableTableIncrementDepth(table);
    variableTableSetVariable(table, "nomnomnom", 5.1, false);
    node = variableTableGetVariable(table, "nomnomnom");
    printf("{%s -> %lf}\n", node->name, node->value);

    variableTableSetVariable(table, "rm", 7.1, false);
    node = variableTableGetVariable(table, "rm");
    printf("{%s -> %lf}\n", node->name, node->value);
  variableTableDecrementDepth(table);

  assert(variableTableGetVariable(table, "rm") == NULL);
  node = variableTableGetVariable(table, "nomnomnom");
  printf("{%s -> %lf}\n", node->name, node->value);

  return 0;
}
