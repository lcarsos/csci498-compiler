#pragma once
#include <iostream>
#include <string>
#include <vector>

class ASTNode {

public:
	enum Type {
		Block,
		Else,
		Empty,
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
	std::string str;
	std::vector<ASTNode> children;

	ASTNode()
	: type(Empty), str() {}
	ASTNode(Type type, std::string str = "")
	: type(type), str(str) {}
};

std::ostream& operator<<(std::ostream& os, ASTNode& node);

namespace std {
	std::string to_string(const ASTNode& node);
	std::string to_string(ASTNode::Type type);
}
