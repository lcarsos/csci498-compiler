#include "ast.h"

using namespace std;

ASTNode::ASTNode(){
	this->type = NodeType::Empty;
	parent = nullptr;
	leftMostSibling = nullptr;
}

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
	addChild(node, getRightMostChild());
}

void ASTNode::addChild(ASTNode* node, ASTNode* right){
	node->parent = this;
	right->rightSibling = shared_ptr<ASTNode>(node);
	node->leftMostSibling = right->leftMostSibling;
}

void ASTNode::addChildren(ASTNode* node){
	auto current = node;
	auto lag = getRightMostChild();
	while (current){
		addChild(current, lag);
		lag = current;
		current = current->rightSibling.get();
	}
}

ASTNode* ASTNode::getLeftMostChild(){
	return leftMostChild.get();
}

ASTNode* ASTNode::getRightMostChild(){
	auto current = leftMostChild.get();

	if (!current)
		return nullptr;

	auto temp = current->rightSibling.get();
	while (temp){
		current = temp;
		temp = current->rightSibling.get();
	}

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

ASTNode::NodeType ASTNode::getType() {
	return type;
}
