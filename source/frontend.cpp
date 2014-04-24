#include "language_0_parser.hpp"

#include <iostream>

// Not declared in the header.
int yyparse();

int main() {
// Enable this when you need token-by-token debugging.
//	yydebug = 1;
	int result = yyparse();
	switch (result) {
		case 0:
			// Silence is golden.
			break;
		case 1:
			// Bison prints syntax errors, so we won't.
			break;
		case 2:
			std::cout << "Memory error!" << std::endl;
			break;
		default:
			std::cout << "Unknown error." << std::endl;
	}
	return result;
}
