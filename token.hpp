#pragma once

#include <iostream>
#include <string>

struct Token {
	// There is a copy-pasted list of strings which depends on this.
	// CHANGE THE VECTOR IN token.cpp IF YOU CHANGE THIS.
	enum token_type {
		Error,
		Number,
		Identifier,
		EoF,
	};
	// TODO: Rename this.
	static std::string token_str(token_type type);

	Token()
		: type(Token::Error), value("") {}
	Token(token_type type, const std::string& value)
		: type(type), value(value) {}

	operator bool();

	token_type type;
	std::string value;
};

std::ostream& operator<<(std::ostream& os, const Token& tok);

// Defined in flex. We put it here for convience.
extern Token nextToken();
