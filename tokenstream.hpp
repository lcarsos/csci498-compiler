#pragma once

#include "token.hpp"

#include <istream>
#include <sstream>
#include <string>

class TokenStream {
public:
	~TokenStream();
	TokenStream();
	TokenStream(std::istream& is);

	void loadStream(std::istream& is);

	Token nextToken();
};
