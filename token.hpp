#pragma once

#include <iostream>
#include <string>

struct Token {
	enum token_type {
		None,
		Number,
		Identifier,
		EoF,
	};

	Token()
		: type(Token::None), value("") {}
	Token(token_type type, const std::string& value)
		: type(type), value(value) {}

	token_type type;
	std::string value;
};

inline std::ostream& operator<<(std::ostream& os, const Token& tok) {
	return os << " (" << tok.type << ", \"" << tok.value << "\")";
}
