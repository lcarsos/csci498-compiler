/*
	The option 'always-interactive' promises flex we're using a terminal/stdin.
	This saves us a check against fileno, which I'm having issues making
	work on Windows. :( For this assignment, we're only using stdin, so we can
	safely surpress this bug and deal with it later.
	TODO: Fix the 'fileno' problem on MinGW/Windows.
*/
%option always-interactive

%{

#include "token.hpp"

#define YY_DECL Token nextToken()
; // This is to keep syntax highlighting happy.

unsigned int line = 1;

%}

%%

[ \t\r\n]+              { continue; } // Ignore whitespace.
[0-9]+                  { return Token(Token::Type::Number, yytext); }
[0-9][a-zA-Z_0-9]+      {
                          // Flex will match this as a single digit number and an ID.
                          //     but it's an error!
                          return Token(Token::Type::Error, yytext);
}
[a-zA-Z_]+[a-zA-Z_0-9]* { return Token(Token::Type::Identifier, yytext); }
<<EOF>>                 { return Token(Token::Type::EoF, ""); }
.                       { return Token(Token::Type::Error, yytext); }

%%
