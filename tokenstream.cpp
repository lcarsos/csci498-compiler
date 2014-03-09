#include "tokenstream.hpp"

TokenStream::~TokenStream() {
	void yy_delete_buffer(void*);
	yy_delete_buffer(buffer);
}

TokenStream::TokenStream()
	: buffer(nullptr) {}

TokenStream::TokenStream(std::istream& is)
	: buffer(nullptr) {
	loadStream(is);
}

TokenStream::operator bool() const {
	return buffer != nullptr;
}

void TokenStream::loadStream(std::istream& is) {
	std::stringstream ss;
	ss << is.rdbuf();
	void* yy_scan_string(void*);
	yy_scan_string(buffer);
}

Token TokenStream::nextToken() {
	Token yylex();
	return yylex();
}
