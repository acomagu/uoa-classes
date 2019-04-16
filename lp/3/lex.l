%{
#include <stdio.h>
%}

%%
" "	;
[+\-*/]	printf("OPERATOR\n");
[0-9]+	printf("NUMBER\n");
\(	printf("OPEN PAREN\n");
\)	printf("CLOSE PAREN\n");
%%

int main() {
  yylex();
  return 0;
}

int yywrap() {
  return 0;
}

int yyerror() {
  printf("Error\n");
  exit(1);
}
