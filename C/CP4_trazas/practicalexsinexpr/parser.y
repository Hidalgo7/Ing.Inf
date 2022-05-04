%{
   #include <stdio.h>
   #include <iostream>
   #include <vector>
   #include <string>
   using namespace std; 

   extern int yylex();
   extern int yylineno;
   extern char *yytext;
   string tab = "\t" ;
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
%token <str> TMUL TPLUS
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
           { cout << "\n<programa>\n" + *$1 + tab + *$2 + tab + *$3 + tab + *$4 + tab + *$5 + tab + *$6 + "\n<\\programa>\n" << endl ;}
        ;

listasentencias : sentencia TSEMIC
         { $$ = new string ; *$$ = "\n<listasentencias1>\n" + *$1 + tab + *$2 + "\n<\\listasentencias1>\n" ;}      
		| listasentencias sentencia TSEMIC
         { $$ = new string ; *$$ = "\n<listasentencias2>\n" + *$1 + tab + *$2 + tab + *$3 + "\n<\\listasentencias2>\n" ;}
        ;

sentencia :  TIDENTIFIER TASSIG expr 
         { $$ = new string ; *$$ = "\n<sentencia>\n" + *$1 + tab + *$2 + tab + *$3 + "\n<\\sentencia>\n" ;}
        ;

expr : expr TMUL expr 
     { $$ = new string; *$$ = "\n<expr>\n" + *$1 + tab + *$2 + tab + *$3 + "\n<\\expr>\n" ; delete $1; delete $3; }
     | expr TPLUS expr 
     { $$ = new string; *$$ = "\n<expr>\n" + *$1 + tab + *$2 + tab + *$3 + "\n<\\expr>\n" ; delete $1; delete $3; }
     | TIDENTIFIER	{ $$ = new string; *$$ = *$1; delete $1; }
     | TINTEGER		{ $$ = new string; *$$ = *$1; delete $1; }
     | TDOUBLE		{ $$ = new string; *$$ = *$1; delete $1; }
     ;

