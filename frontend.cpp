#include "language_0_parser.hpp"

#include <iostream>

using namespace std;

int main() {
	// Enables debugging Bison.
	yydebug = 1;

	switch (yyparse()) {
		case 0:
			// All is good!
			cout << "No errors with yyparse()!\n";
			break;
		case 1:
			cout << "Syntax error!\n";
			break;
		case 2:
			cout << "Memory error!\n";
			break;
		default:
			cout << "Unknown error.\n";
	}
}
