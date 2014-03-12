#pragma once

#include <iostream>
#include <string>

struct Token {
	// Changes here must be mirrored in token_str() in token.cpp.
	enum class Type {
		Error,
		Number,
		Identifier,
		EoF,
		Count,
	};
	// TODO: Rename this.
	static std::string token_str(Type type);

	Token()
		: type(Type::Error), value("") {}
	Token(Type type, const std::string& value)
		: type(type), value(value) {}

	operator bool();

	Type type;
	std::string value;
};

std::ostream& operator<<(std::ostream& os, const Token& tok);

// Defined in flex. We put it here for convience.
extern Token nextToken();
