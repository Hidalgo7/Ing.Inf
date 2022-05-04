%{
   #include <stdio.h>
   #include <iostream>
   #include <vector>
   #include <string>
   using namespace std; 

   extern int yylex();
   extern int yylineno;
   extern char *yytext;
   void yyerror (const char *msg) {
     printf("line %d: %s at '%s'\n", yylineno, msg, yytext) ;
   }

%}

/* 
   qué atributos tienen los tokens 
*/
%union {
    string *str ; 
}

/* 
   declaración de tokens. Esto debe coincidir con tokens.l 
*/
%token <str> TIDENTIFIER TINTEGER TDOUBLE
%token <str> TMUL
%token <str> TSEMIC TASSIG
%token <str> RPROGRAM RBEGIN RENDPROGRAM

%type <str> programa
%type <str> listasentencias
%type <str> sentencia
%type <str> expr

%start programa

%%

programa : RPROGRAM  
           TIDENTIFIER 
	   RBEGIN
	   listasentencias
	   RENDPROGRAM TSEMIC
        ;

listasentencias : sentencia TSEMIC
      | listasentencias sentencia TSEMIC
      ;

sentencia :  TIDENTIFIER TASSIG expr ;

expr : TIDENTIFIER
     | TINTEGER
     | TDOUBLE
     ;

