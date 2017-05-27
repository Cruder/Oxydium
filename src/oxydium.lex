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
%%

{empty}  { /* Nothing */ }



"("   return(OP_PAR);
")"   return(CL_PAR);


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
":"   { return COLON; }
"="   { return EQUAL; }

{comment}   { return(COMMENT); }

"\n"   { return(EOL); }
