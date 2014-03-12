#include "token.hpp"

#include <fstream>
#include <iostream>

using namespace std;

int main() {
	Token tok;
	do {
		tok = nextToken();
		if (tok.type == Token::Error) {
			cerr << "Unrecognized token: '" << tok.value << "'." << endl;
			continue;
		}
		cout << tok << endl;
	} while (tok);

}
