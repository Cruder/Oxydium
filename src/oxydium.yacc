%{
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include "tree.h"
#include "tree_eval.h"
#include "variable_table.h"

extern int  yyparse();
extern int yylex (void);
extern FILE *yyin;
int yyerror(char *s);
double exec(Node *node);

OxydiumExec* oxydium_exec;

%}

%union {
	struct Node *node;
	double val;
	int boolean;
	char* var;
}

%token   <node> NUM
%token   <node> PLUS MIN MULT DIV POW
%token   <node> TOK_EQ NOT_EQ SUP_EQ INF_EQ SUP INF TRUE FALSE
%token   <var> VARIABLE
%token   VAR_TOKEN VAL_TOKEN
%token   OP_PAR CL_PAR COLON
%token   NEG
%token   COMMENT EOL EQUAL DVT
%token 	 PIPE_OP TOK_EQ NOT_EQ SUP_EQ INF_EQ SUP INF
%token 	 IF ELSE BLOCK_START BLOCK_STOP
%token 	 TRUE FALSE

%type   <node> Line
%type   <node> Expr
%type   <node> Block
%type   <node> Boolean
%type   <node> Input
%type   <node> Assignement
%type   <node> Condition
%type   <node> Math
%type   <node> Function

%left PLUS MIN
%left MULT DIV
%left NEG
%right POW

%start Language
%%

Language:
	| Input {}
	;

Input:
      				 {}
  | Line Input { $$ = $1; }

Line:
    EOL 		 { $$ = createNode(NTEMPTY); }
  | Expr EOL { $$ = $1; exec($1); }
  ;

Block:
		BLOCK_START Input BLOCK_STOP { $$=$2; }
	;

Boolean:
		Expr TOK_EQ Expr { $$=nodeChildren($2, $1, $3); }
	|	Expr NOT_EQ Expr { $$=nodeChildren($2, $1, $3); }
	|	Expr SUP_EQ Expr { $$=nodeChildren($2, $1, $3); }
	| Expr INF_EQ Expr { $$=nodeChildren($2, $1, $3); }
	| Expr SUP 		Expr { $$=nodeChildren($2, $1, $3); }
	| Expr INF    Expr { $$=nodeChildren($2, $1, $3); }
	| TRUE						 { $$=$1; }
	| FALSE 					 { $$=$1; }
	;

Assignement:
		VAR_TOKEN VARIABLE EQUAL Expr {
			variableTableSetVariable(oxydium_exec->variable_table, $2, exec($4), false);
			$$=$4;
		}
	| VAL_TOKEN VARIABLE EQUAL Expr {
			variableTableSetVariable(oxydium_exec->variable_table, $2, exec($4), true);
			$$=$4;
		}
	| VARIABLE EQUAL Expr {
			VariableNode* node = variableTableGetVariable(oxydium_exec->variable_table, $1);
			if(node) {
				if(!node->constant) {
					variableTableUpdateVariable(node, exec($3));
				} else {
					fprintf(stderr, "[ERROR] The variable %s is a constant\n", $1);
					exit(1);
				}
			} else {
				fprintf(stderr, "[ERROR] The variable %s does not exist\n", $1);
				exit(1);
			}
			$$=createNode(NTEMPTY);
		}
	;

Condition:
		IF Boolean Block 						{ printf("Condition code 1\n"); $$ = $2 ? $3 : createNode(NTEMPTY); }
	|	IF Boolean Block ELSE Block { printf("Condition code 2\n"); $$ = $2 ? $3 : $5; }
	| Expr IF Boolean 						{ printf("Condition code 3\n"); $$ = $3 ? $1 : createNode(NTEMPTY); }
	;

Math:
		NUM            		 { $$=$1; }
	| Expr PLUS Expr     { $$=nodeChildren($2, $1, $3); }
	| Expr MIN Expr      { $$=nodeChildren($2, $1, $3); }
	| Expr MULT Expr     { $$=nodeChildren($2, $1, $3); }
	| Expr DIV Expr      { $$=nodeChildren($2, $1, $3); }
//	| MIN Expr %prec NEG { ; }
	| Expr POW Expr      { $$=nodeChildren($2, $1, $3); }

// Should be done with Function Workflow
Function:
		VARIABLE OP_PAR Expr CL_PAR {
			printf("function(%s) => %lf\n", $1, $3->val);
			$$=$3;
		}
	| VARIABLE PIPE_OP VARIABLE OP_PAR Expr CL_PAR {
			printf("function(%s) => %lf\n", $3, $5->val);
			$$=$5;
		}
	;

Expr:
		COMMENT							 { $$=createNode(NTEMPTY); }
	| Condition 					 { printf("Condition code\n"); $$ = $1; }
	| Assignement 				 { $$ = $1; }
	| Math 								 { $$ = $1; }
	| Function { $$ = $1; }
	| VARIABLE {
		Node* node = createNode(NTNUM);
		node->val = variableTableGetVariable(oxydium_exec->variable_table, $1)->value;
		$$=node;
	}
  | OP_PAR Expr CL_PAR { $$=$2; }
	| DVT								 {
		variableTableDisplay(oxydium_exec->variable_table);
		$$=createNode(NTEMPTY);
	}
  ;

%%


double exec(Node *node) {
	// printGraph(node);
	return eval(node);
}

int yyerror(char *s) {
  // printf("%s\n", s);
	return 0;
}

int main(int arc, char **argv) {
	if(arc != 3 || strcmp(argv[1], "-f") != 0) { return 1; }

	FILE *fp = fopen(argv[2],"r");
	if(!fp) {
    printf("Impossible d'ouvrir le fichier à executer.\n");
    exit(0);
  }
	oxydium_exec = oxydiumExecCreate(variableTableCreate());

  yyin=fp;
  yyparse();

  fclose(fp);

  return 0;
}
