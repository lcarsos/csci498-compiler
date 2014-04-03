#pragma once
#include <iostream>
#include <string>
#include <vector>

class ASTNode {

public:
	// When adding to this, remember to adjust std::to_string in ast.cpp!
	enum Type {
		Empty,
		Assignment,
		Block,
		Declaration,
		Else,
		Expression,
		If,
		Literal,
		Operator,
		Return,
		Symbol,
		While,
	};

	void addChild(ASTNode node);

	Type type;
	bool isConst; // Only used by Symbol.
	std::string str;
	std::vector<ASTNode> children;

	ASTNode()
	: type(Empty), isConst(false), str() {}
	ASTNode(Type type, std::string str = "")
	: type(type), isConst(false), str(str) {}

	void makeConst();
	void makeUnconst();
};

std::ostream& operator<<(std::ostream& os, ASTNode& node);

std::string to_string(const ASTNode& node);
std::string to_string(ASTNode::Type type);
