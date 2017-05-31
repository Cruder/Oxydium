%option noyywrap
%{

#include "oxydium.h"
#include <stdlib.h>
#include "tree.h"

%}

empty    [ \t]+

num   [0-9]
int    {num}+
exp  [eE][+-]?{int}

real      {int}("."{int})?{exp}?
comment   [#].+

val       (val)
var       (var)

variable [a-zA-Z](?:[a-zA-Z_0-9]+)?[\?!]?

display_table (!display_variable_table!)
%%

{empty}  { /* Nothing */ }
{real}    {
    yylval.node = createNode(NTNUM);
    yylval.node->val = atof(yytext);
    return(NUM);
    }

{val} { return VAL_TOKEN; }
{var} { return VAR_TOKEN; }

{variable} {
    yylval.var = (char*)strdup(yytext);
    return VARIABLE;
}

"+"   { yylval.node = createNode(NTPLUS); return(PLUS); }
"-"   { yylval.node = createNode(NTMIN); return(MIN); }
"*"   { yylval.node = createNode(NTMULT); return(MULT); }
"/"   { yylval.node = createNode(NTDIV); return(DIV); }
"^"   { yylval.node = createNode(NTPOW); return(POW); }
"("   { return OP_PAR; }
")"   { return CL_PAR; }
":"   { return COLON; }
"="   { return EQUAL; }
"|>"  { return PIPE_OP; }

"=="  { return TOK_EQ; }
"!="  { return NOT_EQ; }
">="  { return SUP_EQ; }
"<="  { return INF_EQ; }
">"   { return SUP; }
"<"   { return INF; }

{comment}   { return(COMMENT); }

"\n"    { return(EOL); }
"if"    { return IF; }
"true"  { return TRUE; }
"false" { return FALSE; }

{display_table} { return DVT; }
