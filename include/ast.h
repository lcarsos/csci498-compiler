#pragma once
#include <vector>
#include <memory>
#include <string>

class ASTNode {

public:

	enum NodeType {
		Literal, Symbol, Operator, Empty
	};

	// All node creation goes through this function
	static ASTNode* makeNode(NodeType type, std::string str = "");

	void addChild(ASTNode* node);

	// removes children and returns them
	std::shared_ptr<ASTNode> removeChildren();

	ASTNode* getLeftMostChild();
	ASTNode* getRightMostChild();

	// by value so we create a new string
	std::string getStr();

	NodeType getType();

protected:
	ASTNode(NodeType type, std::string str);

	std::shared_ptr<ASTNode> leftMostChild;
	ASTNode* parent; // non-ownership ptr
	ASTNode* leftMostSibling; // non-ownership ptr
	std::shared_ptr<ASTNode> rightSibling;
	NodeType type; // we might want to do subclasses instead
	std::string str;  // many types have important information to store here
};