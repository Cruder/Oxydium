#ifndef __NODE_TREE_H__
#define __NODE_TREE_H__

#include <stdlib.h>
#include "oxydium_exec.h"

enum NodeType {
	NTEMPTY = 0,
	NTSUITE = 1,

	NTNUM    = 201,
	NTVAR    = 202,
	NTSTRING = 203,

	NTPLUS  = 301,
	NTMIN   = 302,
	NTMULT  = 303,
	NTDIV   = 304,
	NTPOW   = 305,

	NTIF    = 401,

	NTVARINIT = 501,
	NTVALINIT = 502,

	NTTOK_EQ = 601,
	NTNOT_EQ = 602,
	NTSUP_EQ = 603,
	NTINF_EQ = 604,
	NTSUP    = 605,
	NTINF    = 606,

	NTTRUE	 = 651,
	NTFALSE  = 652
};

typedef struct Node {
	enum NodeType type;

	double 				val;
	char* 				var;
	struct Node** children;
	size_t 				children_count;
	// NodeExec*			suite;
} Node;

Node* 			createNode(int type);
Node* 			nodeChildren(Node* father, Node *child1, Node *child2);
const char* node2String(Node *node);
void 				printGraph(Node *root);
void 				nodeDestroy(Node* node);

#endif /* end of include guard: __NODE_TREE_H__ */
