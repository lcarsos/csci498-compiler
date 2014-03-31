#include "ast.h"

using namespace std;

ASTNode::ASTNode(NodeType type, string str){
	this->type = type;
	this->str = str;
	parent = nullptr;
	leftMostSibling = nullptr;
}

ASTNode* ASTNode::makeNode(NodeType type, string str){
	return new ASTNode(type, str);
}

void ASTNode::addChild(ASTNode* node){
	node->parent = this;
	auto right = getRightMostChild();
	right->rightSibling = shared_ptr<ASTNode>(node);
	node->leftMostSibling = right->leftMostSibling;
}

ASTNode* ASTNode::getLeftMostChild(){
	return leftMostChild.get();
}

ASTNode* ASTNode::getRightMostChild(){
	auto current = leftMostChild.get();

	if (!current)
		return nullptr;

	ASTNode* temp;
	while (temp = current->rightSibling.get())
		current = temp;

	return current;
}

shared_ptr<ASTNode> ASTNode::removeChildren(){
	shared_ptr<ASTNode> node;
	node.swap(leftMostChild);

	auto current = node.get();

	while (current){
		current->parent = nullptr;
		current = current->rightSibling.get();
	}

	return node;
}

string ASTNode::getStr(){
	return str;
}