#ifndef OXYDIUM_EXEC
#define OXYDIUM_EXEC

#include "tree.h"
#include "variable_table.h"

struct Node;

typedef struct NodeExec {
  struct NodeExec* next;
  struct NodeExec* previous;

  struct Node* head;
} NodeExec;

typedef struct OxydiumExec{
  VariableTable* variable_table;
  NodeExec*      current_node;
  NodeExec*      head;
} OxydiumExec;

OxydiumExec* oxydiumExecCreate(VariableTable* variable_table);
void         oxydiumExecDestroy(OxydiumExec* exec);
void         nodeExecDestroy(NodeExec* node);

void         oxydiumExecPushNode(OxydiumExec* exec, struct Node* node);

#endif /* end of include guard: OXYDIUM_EXEC */
