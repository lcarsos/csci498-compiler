#include "token.hpp"

#include <iostream>

using namespace std;

int main() {
	Token tok;

	cout << Token(Token::Type::EoF, "???") << endl;

	do {
		tok = nextToken();
		if (tok.type == Token::Type::Error) {
			cerr << "Unrecognized token: '" << tok.value << "'." << endl;
			continue;
		}
		cout << tok << endl;
	} while (tok);

}
