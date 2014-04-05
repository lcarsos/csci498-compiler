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
	// Only used by Symbol.
	bool isConst;
	// Some nodes (e.g. int and float literals) need to save data, but not
	//   as strings.
	// TODO: More flexibility in type stored.
	std::string str;

	// TODO: Children should know about their parent.
	std::vector<ASTNode> children;

	ASTNode()
	: type(Type::Empty), isConst(false) {}
	ASTNode(Type type, std::string str = "")
	: type(type), isConst(false), str(str) {}

	void makeConst();
	void makeUnconst();
};

std::ostream& operator<<(std::ostream& os, ASTNode& node);

std::string to_string(const ASTNode& node);
std::string to_string(ASTNode::Type type);
