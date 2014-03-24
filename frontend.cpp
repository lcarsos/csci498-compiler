#include "language_0_parser.hpp"

#include <iostream>

using namespace std;

int main() {
	// Enables debugging Bison.
	yydebug = 1;

	int result = yyparse();
	cout << "yyparse(): " << result << "\n";
}
