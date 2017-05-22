#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <setjmp.h>
#include "node_tree.h"
#include "node_eval.h"

double evalExpr(Node *node) {
	switch ( node->type ) {
	case NTEMPTY:  return 0.0;
	case NTNUM: return node->val;

	case NTPLUS: return evalExpr(node->children[0])
			+ evalExpr(node->children[1]);
	case NTMIN: return evalExpr(node->children[0])
			- evalExpr(node->children[1]);
	case NTMULT: return evalExpr(node->children[0])
			* evalExpr(node->children[1]);
	case NTDIV: return evalExpr(node->children[0])
			/ evalExpr(node->children[1]);
	case NTPOW: return pow(evalExpr(node->children[0]),
			evalExpr(node->children[1]));
	default:
		printf("Error in evalExpr ... Wrong node type: %s\n", node2String(node));
		exit(1);
	};
}

int evalInst(Node* node) {
	double val;
	switch ( node->type ) {
	case NTEMPTY: return 0;
	case NTINSTLIST:
		 case NTNUM:
	case NTPLUS:
	case NTMIN:
	case NTMULT:
	case NTDIV:
	case NTPOW:
		printf("%f\n", evalExpr(node));
		return 0;

	default:
		printf("Error in evalInst ... Wrong node type: %s\n", node2String(node));
		exit (1);
	};

	return 0;
}

int eval(Node *node) {
	return evalInst(node);
}
