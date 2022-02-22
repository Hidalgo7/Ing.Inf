
%{
 #include <string>
 #include <iostream>
 #include <vector>
 #include "traza.hpp" 
 using namespace std ;

 #define TOKEN(t) processtoken(t, string(yytext, yyleng))

 void processtoken (int t, string id) {
   cout << t << " <" << id << ">" << endl ;
 }

%}
%option nounput
%%
def                     TOKEN(RDEF);
main                    TOKEN(RMAIN);
let	                    TOKEN(RLET);
in                      TOKEN(RIN);
id                      TOKEN(RID);
integer                 TOKEN(RINTEGER);
float                   TOKEN(RFLOAT);
if                      TOKEN(RIF);
while                   TOKEN(RWHILE);
else                    TOKEN(RELSE);
forever                 TOKEN(RFOREVER);
break                   TOKEN(RBREAK);  
continue                TOKEN(RCONTINUE);
read                    TOKEN(RREAD);
println                 TOKEN(RPRINTLN);

"*"                     TOKEN(TMUL);

":="                    TOKEN(TASSIG);

","                     TOKEN(TCOMMA);

":"                     TOKEN(TDBLDOT);

";"                     TOKEN(TSEMIC);

"("                     TOKEN(TLPAREN);

")"                     TOKEN(TRPAREN);

"{"                     TOKEN(TLBRACE);

"}"                     TOKEN(TRBRACE);

"&"                     TOKEN(TAMP);

"="                     TOKEN(TEQUAL);

"=="                    TOKEN(TCEQ);

">"                     TOKEN(TCGT);

"<"                     TOKEN(TCLT);

">="                    TOKEN(TCGE);

"<="                    TOKEN(TCLE);

"/="                    TOKEN(TCNE);

"+"                     TOKEN(TPLUS);

"-"                     TOKEN(TMINUS);

"/"                     TOKEN(TDIV);

#[^#\n]+\n                printf("\nCOMENTARIO\n");

[ \t\n]                 ;

[a-zA-Z](_?[a-zA-Z0-9]+)*    TOKEN(TIDENTIFIER) ; 
[0-9]+\.[0-9]+([Ee][+-]?[0-9]+)?        TOKEN(TDOUBLE);
[0-9]+                  TOKEN(TINTEGER);

 TOKEN(T28);

.                       { cout << "Token desconocido: " << yytext << endl; yyterminate();}
%%

int main() {
  yylex() ;
  cout << "Ha finalizado." << endl ; 
}
