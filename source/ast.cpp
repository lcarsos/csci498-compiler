#include "ast.h"

#include <functional>
#include <sstream>
#include <unordered_map>

unsigned int IRInst::registerCount = 0;
int ASTNode::nodeCount = 0;

void ASTNode::addChild(const ASTNode& node) {
    children.push_back(node);
}

void ASTNode::find_all_children(std::vector<ASTNode>& nodes) const {
    nodes.push_back(*this);
    for (const ASTNode& child : children) {
        child.find_all_children(nodes);
    }
}

void ASTNode::print_tree(std::ostream& os) {
    std::vector<ASTNode> allChildren;
    find_all_children(allChildren);

    // We print the uniqueID of each node and its name first and foremost.
    for (const ASTNode& node : allChildren) {
        os << node.uniqueID << " " << to_string(node) << std::endl;
    }
    // Separate the 'declarations' and 'definitions'.
    os << "\n";

    // Print the uniqueID of each node and all of its children.
    for (const ASTNode& node : allChildren) {
        if (node.children.size() < 1) {
            // Skip over leaves, as they have no children.
            continue;
        }
        os << node.uniqueID << " ";
        for (const ASTNode& child : node.children) {
            os << child.uniqueID << " ";
        }
        os << std::endl;
    }

}

std::vector<IRInst> ASTNode::generate_ir() {
    //TODO: add symbol function
    std::vector<IRInst> result;
    switch (type) {
        case Empty:
            //TODO: Return Error
            return result;
        case Assignment:
            // generate_ir on RHS -> RX
            // memst RX, @(LHS)
            return result;
        case Block:
            // generate_ir on all children
            // pass vector on
            return result;
        case Declarations:
            // First Child is always type
            // All children afterwards are symbols or assignment
            //      first child of assignment is symbol to add to table

            // if symbol in scope
            //      error
            // else
            //    add to table
            //
            // if assignment
            //    generate_ir for assignment
            //  
            return result;
        case Expression:
            //Return calc RD, <Expr>
            return result;
        case If:
            return result;
        case Program:
            //Concat children
            return result;
        case Return:
            // ircode: return
            return result;
        case Symbol:
            // error (maybe)
            return result;
        case While:
            // Like if
            return result;
    }
}

void ASTNode::print_ir(std::ostream& os) {

}

void ASTNode::makeConst() {
    isConst = true;
}

std::string to_string(const ASTNode& node) {
    std::string str;
    // TODO: Stop copying over 200 nodes before any of the final ones,
    //   which appear in the graph, are created.
    // str += "#" + to_string(node.uniqueID) + " ";
    if (node.type != ASTNode::Symbol) {
        str += to_string(node.type);
    }
    if (node.str.length() >= 1) {
        if (node.isConst) {
            str += " const";
        }
        str += " '" + node.str + "'";
    }
    if (str.length() == 0) {
        static int errorCount = 1;
        str = "Error #" + std::to_string(errorCount);
        errorCount += 1;
    }
    return str;
}

std::string to_string(ASTNode::Type type) {
    switch (type) {
    // Make sure every case is handled, when changing the enum declaration
    //   in ast.h.
    case ASTNode::Empty:        return "Empty";
    case ASTNode::Assignment:   return "Assignment";
    case ASTNode::Block:        return "Block";
    case ASTNode::Declarations: return "Declarations";
    case ASTNode::Expression:   return "Expression";
    case ASTNode::If:           return "If";
    case ASTNode::Program:      return "Program";
    case ASTNode::Return:       return "Return";
    case ASTNode::Symbol:       return "Symbol";
    case ASTNode::While:        return "While";
    default:
        return "? (" + std::to_string((size_t)type) + ")";
    }
}

bool operator==(const ASTNode& a, const ASTNode& b) {
    return a.uniqueID == b.uniqueID;
}
