#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <setjmp.h>
#include "tree.h"
#include "tree_eval.h"

double evalExpr(Node *node);

bool booleanExpr(Node* node) {
	Node* c1 = node->children[0];
	Node* c2 = node->children[1];
	switch (node->type) {
		case NTTOK_EQ: return evalExpr(c1) == evalExpr(c2);
		case NTNOT_EQ: return evalExpr(c1) != evalExpr(c2);
		case NTSUP_EQ: return evalExpr(c1) >= evalExpr(c2);
		case NTINF_EQ: return evalExpr(c1) <= evalExpr(c2);
		case NTSUP: 	 return evalExpr(c1) >  evalExpr(c2);
		case NTINF: 	 return evalExpr(c1) <  evalExpr(c2);
		case NTTRUE: 	 return true;
		case NTFALSE:  return true;

		default:
			fprintf(stderr, "[ERROR] Node type: %s\n", node2String(node));
			exit(node->type);
	}
}

double mathExpr(Node* node) {
	Node* c1 = node->children[0];
	Node* c2 = node->children[1];
	switch (node->type) {
		case NTPLUS: return evalExpr(c1) + evalExpr(c2);
		case NTMIN:  return evalExpr(c1) - evalExpr(c2);
		case NTMULT: return evalExpr(c1) * evalExpr(c2);
		case NTDIV:  return evalExpr(c1) / evalExpr(c2);
		case NTPOW:  return pow(evalExpr(c1), evalExpr(c2));

		default:
			fprintf(stderr, "[ERROR] Node type: %s\n", node2String(node));
			exit(node->type);
	}
}


double evalExpr(Node *node) {
	if(node->type == NTEMPTY) { return 0.0; }
	// else if(node->type > 200 && node->type < 300) { booleanExpr(node); }
	// else if(node->type > 300 && node->type < 400) { booleanExpr(node); }
	// else if(node->type > 600 && node->type < 700) { booleanExpr(node); }

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

double evalInst(Node* node) {
	double val;
	switch (node->type) {
	case NTEMPTY: return 0;
	case NTSUITE:
	case NTNUM:
	case NTPLUS:
	case NTMIN:
	case NTMULT:
	case NTDIV:
	case NTPOW:
		return evalExpr(node);
	default:
		printf("Error in evalInst ... Wrong node type: %s\n", node2String(node));
		exit (1);
	};

	return 0;
}

double eval(Node *node) {
	return evalInst(node);
}
