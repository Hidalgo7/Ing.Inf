string [a-zA-Z][a-zA-Z0-9]*
special_string [{string}?%&$\*\)\(]^(\*\))
%%
\(\*[{special_string} ]*\*\)	                 { printf("%s:\tSI\n",yytext); }
\n					 ;					 
.+   	                       		 { printf("%s:\tNO\n",yytext); }
%%