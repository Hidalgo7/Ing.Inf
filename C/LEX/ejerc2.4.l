%{
int contId = 0;
int contReal = 0;
%}
string [a-zA-Z][a-zA-Z0-9]*
int [0-9]+

%%
[Pp][Rr][Oo][Cc][Ee][Dd][Uu][Rr][Ee] ;
[Bb][Ee][Gg][Ii][Nn]                 ;
[Ee][Nn][Dd]                         ;
\/\/(.)*\n                           ;
\-?{int}\.{int}([Ee][+-]?{int})?	 {aumentarReal();}
{string}(_[a-zA-Z0-9]+)*	         {aumentarId();}
\n    				     ;
.      				     ;
%%
main() {
  yylex() ;
  printf("Numero de IDs: %d\nNumero de Reales: %d\n",contId,contReal);
}
aumentarId() {
  contId++;
}

aumentarReal() {
  contReal++;
}

