%{

#include "token.hpp"

#define YY_DECL Token nextToken()
; // This is to keep syntax highlighting happy.

unsigned int line = 1;

%}

%%

[ \t\r\n]+              { continue; } // Ignore whitespace.
[0-9]+                  { return Token(Token::Number, yytext); }
[0-9][a-zA-Z_0-9]+      {
                          // Flex will match this as a single digit number and an ID.
                          //     but it's an error!
                          return Token(Token::Error, yytext);
}
[a-zA-Z_]+[a-zA-Z_0-9]* { return Token(Token::Identifier, yytext); }
<<EOF>>                 { return Token(Token::EoF, ""); }
.                       { return Token(Token::Error, yytext); }

%%
