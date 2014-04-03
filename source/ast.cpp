#include "ast.h"

#include <regex>

using namespace std;

void ASTNode::addChild(ASTNode node) {
	children.push_back(node);
}

void ASTNode::makeConst() {
	isConst = true;
}
void ASTNode::makeUnconst() {
	isConst = false;
}


// Normal, not-pretty printing.
ostream& operator<<(ostream& os, ASTNode& node) {
	os << "(";
	os << "" << to_string(node.type);
	if (node.str.size() >= 1) {
		os << ":\"" << node.str << "\"";
	}
	for (ASTNode child : node.children) {
		os << " " << child;
	}
	os << ")";
	return os;
}

// Pretty print a node and all of its children.
//   Imagine Lisp/Scheme with indenting.
string to_string(const ASTNode& node) {
	string str = "(";
	str += to_string(node.type);
	if (node.str.length() >= 1) {
		str += ":\"" + node.str + "\"";
	}
	for (ASTNode node : node.children) {
		str += to_string(node);
	}
	str += ")";

	string res;
	int depth = 0;
	for (char c : str) {
		switch (c) {
		case '(':
			depth += 1;
			res += "\n";
			for(int i = 0; i < depth; ++i) {
				res += "   ";
			}
			break;
		case ')':
			depth -= 1;
			break;
		// Don't send spaces or newlines to the final string.
		case ' ': case '\n':
			continue;
		}
		res += c;
	}
	// Make sure the first character is a '('
	while (res[0] != '(') {
		res.erase(res.begin());
	}
	return res;
}

string to_string(ASTNode::Type type) {
	switch (type) {
	case ASTNode::Empty:       return "Empty";       break;
	case ASTNode::Assignment:  return "Assignment";  break;
	case ASTNode::Block:       return "Block";       break;
	case ASTNode::Declaration: return "Declaration"; break;
	case ASTNode::Else:        return "Else";        break;
	case ASTNode::Expression:  return "Expression";  break;
	case ASTNode::If:          return "If";          break;
	case ASTNode::Literal:     return "Literal";     break;
	case ASTNode::Operator:    return "Operator";    break;
	case ASTNode::Return:      return "Return";      break;
	case ASTNode::Symbol:      return "Symbol";      break;
	case ASTNode::While:       return "While";       break;
	default:
		return "? (" + to_string((int)type) + ")";
	}
}
