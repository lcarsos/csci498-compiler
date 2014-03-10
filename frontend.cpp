#include "token.hpp"
#include "tokenstream.hpp"

#include <fstream>
#include <iostream>

extern Token yylex();

int main() {
	std::ifstream fi("foo.txt");
	TokenStream input(fi);
	Token tok;
	while ( (tok = input.nextToken()).type != Token::EoF) {
		std::cout << tok << "\n";
	}
}
