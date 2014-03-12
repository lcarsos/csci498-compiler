
#include "token.hpp"

#include <vector>

using namespace std;

string Token::token_str(token_type type) {
	static const vector<string> lookup = {
		"Error",
		"Number",
		"Identifier",
		"EoF",
	};
	// vector::at throws an exception when type is out of bounds.
	// When (not if) someone updates the enum and not the lookup vector,
	//   it will be much easier to catch.
	return lookup.at(type);
}

Token::operator bool() {
	return type != Token::EoF;
}

ostream& operator<<(ostream& os, const Token& tok) {
	return os << " (" << Token::token_str(tok.type) << ", \"" << tok.value << "\")";
}
