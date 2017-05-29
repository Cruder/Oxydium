%{
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "tree.h"
#include "tree_eval.h"
#include "variable_table.h"

extern int  yyparse();
extern int yylex (void);
extern FILE *yyin;
int yyerror(char *s);
double exec(Node *node);

VariableTable* variable_table;

%}

%union {
	struct Node *node;
	double val;
	char* var;
}

%token   <node> NUM
%token   <node> PLUS MIN MULT DIV POW
%token   <var> VARIABLE
%token   VAR_TOKEN VAL_TOKEN
%token   OP_PAR CL_PAR COLON
%token   NEG
%token   COMMENT EOL EQUAL DVT

%type   <node> Line
%type   <node> Expr

%left PLUS MIN
%left MULT DIV
%left NEG
%right POW

%start Input
%%

Input:
      {/* Nothing ... */ }
  | Line Input { }


Line:
    EOL {  }
  | Expr EOL { $$ = $1; exec($1); }
  ;

Expr:
	COMMENT							 { $$=createNode(NTEMPTY); }
	| VAR_TOKEN VARIABLE EQUAL Expr {
		// printf("variable init (%s)\n", $2);
		// printf("-> %s\n", $2);
		variableTableSetVariable(variable_table, $2, exec($4), false);
		$$=$4;
	}
	| VARIABLE EQUAL Expr {
		VariableNode* node = variableTableGetVariable(variable_table, $1);
		if(node) {
			variableTableUpdateVariable(node, exec($3));
		}
		$$=createNode(NTEMPTY);
	}
	| VARIABLE {
		// printf("get variable (%s)\n", $1);
		Node* node = createNode(NTNUM);
		node->val = variableTableGetVariable(variable_table, $1)->value;
		$$=node;
	}
	| VARIABLE OP_PAR Expr CL_PAR {
		printf("function(%s) => %lf\n", $1, $3->val);
		$$=$3;
	}
  | NUM            		 { $$=$1; }
  | Expr PLUS Expr     { $$=nodeChildren($2, $1, $3); }
  | Expr MIN Expr      { $$=nodeChildren($2, $1, $3); }
  | Expr MULT Expr     { $$=nodeChildren($2, $1, $3); }
  | Expr DIV Expr      { $$=nodeChildren($2, $1, $3); }
  | MIN Expr %prec NEG { ; }
  | Expr POW Expr      { $$=nodeChildren($2, $1, $3); }
  | OP_PAR Expr CL_PAR { $$=$2; }
	| DVT								 {
		variableTableDisplay(variable_table);
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
	variable_table = variableTableCreate();

  yyin=fp;
  yyparse();

  fclose(fp);

  return 0;
}
