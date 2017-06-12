#include "oxydium_exec.h"

NodeExec* createNodeExec(NodeExec* previous);

OxydiumExec* oxydiumExecCreate(VariableTable* variable_table) {
  OxydiumExec* exec = (OxydiumExec*)malloc(sizeof(OxydiumExec));
  exec->head = createNodeExec(NULL);
  exec->current_node = exec->head;
  exec->variable_table = variable_table;

  return exec;
}

void oxydiumExecDestroy(OxydiumExec* exec) {
  nodeExecDestroy(exec->head);
  variableTableDestroy(exec->variable_table);

  free(exec);
}

NodeExec* createNodeExec(NodeExec* previous) {
  NodeExec* node = (NodeExec*)malloc(sizeof(NodeExec));

  node->next = NULL;
  node->previous = previous;

  node->head = NULL;

  return node;
}

void nodeExecDestroy(NodeExec* node) {
  nodeExecDestroy(node->next);
  nodeDestroy(node->head);

  free(node);
}

void oxydiumExecPushNode(OxydiumExec* exec, Node* node) {
  NodeExec* new_node = createNodeExec(exec->current_node);
  exec->current_node->next = new_node;
  exec->current_node = new_node;
}
