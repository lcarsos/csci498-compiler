#include "ast.h"

#include <regex>

using namespace std;

void ASTNode::addChild(ASTNode node) {
	children.push_back(node);
}

// Normal, not-pretty printing.
ostream& operator<<(ostream& os, ASTNode& node) {
	os << "(";
	os << "" << to_string(node.type) << ":\"" << node.str << "\"";
	for (ASTNode child : node.children) {
		os << " " << child;
	}
	os << ")";
	return os;
}

namespace std {
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
		case ASTNode::Block:
			return "Block";
		case ASTNode::Else:
			return "Else";
		case ASTNode::Empty:
			return "Empty";
		case ASTNode::Expression:
			return "Expression";
		case ASTNode::If:
			return "If";
		case ASTNode::Literal:
			return "Literal";
		case ASTNode::Operator:
			return "Operator";
		case ASTNode::Return:
			return "Return";
		case ASTNode::Symbol:
			return "Symbol";
		case ASTNode::While:
			return "While";
		default:
			return "? (" + to_string(type) + ")";
		}
	}
}
