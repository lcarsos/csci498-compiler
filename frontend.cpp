#include "token.hpp"
#include "tokenstream.hpp"

#include <iostream>

extern Token yylex();

int main() {
	TokenStream input(std::cin);
	while (input) {
		std::cout << input.nextToken() << "\n";
	}
}
