#include "tokenstream.hpp"

namespace flex {
	void scan_string(const std::string&);
}


TokenStream::~TokenStream() {
}

TokenStream::TokenStream() {}

TokenStream::TokenStream(std::istream& is) {
	loadStream(is);
}

void TokenStream::loadStream(std::istream& is) {
	std::stringstream ss;
	ss << is.rdbuf();
	flex::scan_string(ss.str());
}

Token TokenStream::nextToken() {
	Token yylex();
	return yylex();
}
