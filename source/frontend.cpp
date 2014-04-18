#include "language_0_parser.hpp"

#include <iostream>

// Not declared in the header.
int yyparse();

int main() {
//	yydebug = 1;
	switch (yyparse()) {
		case 0:
			// Silence is golden.
			break;
		case 1:
            std::cout << "Syntax error!" << std::endl;
			break;
		case 2:
            std::cout << "Memory error!" << std::endl;
			break;
		default:
            std::cout << "Unknown error." << std::endl;
	}
}
