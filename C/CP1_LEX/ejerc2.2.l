string [a-zA-Z][a-zA-Z0-9]*
%%
{string}(_{string})*	 { printf("%s:\tSI\n",yytext); }
\n					 ;					 
.+   	                       		 { printf("%s:\tNO\n",yytext); }
%%
