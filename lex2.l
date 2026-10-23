
%{
#include <stdio.h>
%}

%%
"int"|"float"|"char"|"if"|"else"|"while"|"return" {
    printf("%s - Keyword\n", yytext);
}

[a-zA-Z][a-zA-Z0-9]* {
    printf("%s - Identifier\n", yytext);
}

[0-9]+ {
    printf("%s - Number\n", yytext);
}

[+\-*/=<>] {
    printf("%s - Operator\n", yytext);
}

[();{},] {
    printf("%s - Special Symbol\n", yytext);
}

[ \t\n]+    ;
.           ;
%%

int main()
{
    printf("Enter a statement:\n");
    yylex();
    return 0;
}

int yywrap()
{
    return 1;
}
