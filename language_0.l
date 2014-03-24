/*
	The option 'always-interactive' promises flex we're using a terminal/stdin.
	This saves us a check against fileno, which I'm having issues making
	work on Windows. :( For this assignment, we're only using stdin, so we can
	safely surpress this bug and deal with it later.
	TODO: Fix the 'fileno' problem on MinGW/Windows.
*/
%option always-interactive

%{

#include "language_0_parser.hpp"

%}

/* Tokens used here are defined in the bison file.
   TODO: Tokens for binary and uninary operators? */
%%

[+-]?[0-9]+ {
	yylval.integer = atoi(yytext);
	return Integer;
}
[+-]?[0-9]+\.?[0-9]*([eE][+-]?[0-9]+)? {
	yylval.real = atof(yytext);
	return Float;
}
[a-zA-Z_]+[a-zA-Z_0-9]* {
	yylval.identifier = strdup(yytext);
	return Identifier;
}

. {
	// Do nothing with unknown characters.
	continue;
}

%%
