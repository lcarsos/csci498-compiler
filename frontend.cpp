#include "language_0_parser.hpp"

#include <iostream>

using namespace std;

int main() {
	int result = yyparse();
	cout << "yyparse(): " << result << "\n";
}
