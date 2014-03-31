%{

#include "language_0_parser.hpp"

#include <cstring>

%}

%%

[+-]?[0-9]+ {
	yylval.integer = atoi(yytext);
	return integer;
}

[+-]?[0-9]+\.?[0-9]*([eE][+-]?[0-9]+)? {
	yylval.real = atof(yytext);
	return real;
}

[a-zA-Z_]+[a-zA-Z_0-9]* {
	// TODO: Don't use snprintf or strdup.
	strncpy(yylval.identifier, yytext, 999);
	return identifier;
}

"&"|"|"|"^"|">"|"<"|"+"|"-"|"/"|"*"|"&&"|"||"|"<<"|">>" {
	// This depends on the operator only being 1 or 2 characters long.
	//   If it's only 1 long, yytext[1] will be 0 and we end up with the
	//   ASCII representation of the character. Otherwise it's just like
	//   C mutli-char literals.
	// TODO: Return an enum class instead.
	int op = yytext[0] + yytext[1] << 8;
	yylval.op = op;
	return binaryOp;
}

"/"|"*"|"-"|"~"|"!" {
	// This depends on the operator only being 1 or 2 characters long.
	//   If it's only 1 long, yytext[1] will be 0 and we end up with the
	//   ASCII representation of the character. Otherwise it's just like
	//   C mutli-char literals.
	// TODO: Return an enum class instead.
	int op = yytext[0] + yytext[1] << 8;
	yylval.op = op;
	return unaryOp;
}

. {
	// Pass unknown characters through to Bison, they might be important.
	continue;
}

%%
