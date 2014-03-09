#include "token.hpp"

#include <iostream>

extern Token yylex();

int main() {
	Token tok;
	while ( (tok = yylex()).type != Token::EoF ) {
		std::cout << tok << "\n";
	}
}
