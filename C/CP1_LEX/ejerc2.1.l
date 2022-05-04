
int [0-9]+
%%
\-?{int}\.{int}([Ee][+-]?{int})?	 { printf("%s:\tSI\n",yytext); }
\n					 ;					 
.+   	                       		 { printf("%s:\tNO\n",yytext); }
%%

