%option noyywrap
%{

#include "token.hpp"

#define YY_DECL Token yylex()
; // This is to keep syntax highlighting happy.

unsigned int line = 1;

%}

%%
\n                                { line += 1; continue; }
[ \t\r]+                          { continue; } // Ignore whitespace.
[0-9]+                            { return Token(Token::Number, yytext); }
[a-zA-Z_]+[a-zA-Z_0-9]*           { return Token(Token::Identifier, yytext); }
<<EOF>>                           { return Token(Token::EoF, ""); }
