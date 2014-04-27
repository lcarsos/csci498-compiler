#include "ast.h"
#include "symboltable.h"

#include <functional>
#include <sstream>
#include <unordered_map>

std::vector<IRInst> ir_assignment(const ASTNode* node);
std::vector<IRInst> ir_block(const ASTNode* node);
std::vector<IRInst> ir_declarations(const ASTNode* node);
std::vector<IRInst> ir_expression(const ASTNode* node);
std::vector<IRInst> ir_if(const ASTNode* node);
std::vector<IRInst> ir_program(const ASTNode* node);
std::vector<IRInst> ir_return(const ASTNode* node);
std::vector<IRInst> ir_symbol(const ASTNode* node);
std::vector<IRInst> ir_while(const ASTNode* node);

unsigned int IRInst::registerCount = 0;
int ASTNode::nodeCount = 0;
static SymbolTable symT(10000); //You all can kill me later for this

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

std::vector<IRInst> ASTNode::generate_ir() const {
    //TODO: add symbol function
    std::vector<IRInst> result;
    switch (type) {
        case Empty:
            //TODO: Return Error
            return result;
        case Type::Assignment:
            result = ir_assignment(this);
            return result;
        case Type::Block:
            return ir_block(this);
        case Declarations:
            return ir_declarations(this);
        case Expression:
            return ir_expression(this);
        case If:
            return ir_if(this);
        case Program:
            return ir_program(this);
        case Return:
            return ir_return(this);
        case Symbol:
            return ir_symbol(this);
        case While:
            return ir_while(this);;
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



std::vector<IRInst> ir_assignment(const ASTNode* node) {
    // memst RX, @(LHS)
    std::vector<IRInst> result;

    // generate_ir on RHS -> RX
    // Assignments always have two children
    //      Look at language_0.y lines 179 and 199 for proof
    result = node->children[1].generate_ir(); //should call ir_expression()

    std::vector<IRInst> symbolIR = node->children[0].generate_ir();

    result.reserve(result.size() + symbolIR.size());
    result.insert(result.begin(), symbolIR.begin(), symbolIR.end());

    return result;
}

std::vector<IRInst> ir_block(const ASTNode* node) {
    // generate_ir on all children
    // pass vector on
    std::vector<IRInst> result;

    //Create new scope for block
    symT.openScope();

    //Build up result from generate_ir on all children
    std::vector<IRInst> childResult;
    for (ASTNode child : node->children) {
        childResult = child.generate_ir();
        result.reserve(result.size() + childResult.size());
        result.insert(result.end(), childResult.begin(), childResult.end());
    }

    //Close scope for block
    symT.closeScope();

    return result;
}

std::vector<IRInst> ir_declarations(const ASTNode* node) {
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
    std::vector<IRInst> result;


    return result;
}

std::vector<IRInst> ir_expression(const ASTNode* node) {
    //Return calc RD, <Expr>
    std::vector<IRInst> result;

    IRInst calcExpr;

    calcExpr.type = IRInst::Calc;
    calcExpr.destReg = 0;
    calcExpr.nodeID = node->uniqueID;

    result.push_back(calcExpr);

    return result;
}

std::vector<IRInst> ir_if(const ASTNode* node) {
    std::vector<IRInst> result;

    //Calculate if expression, result will be in R0
    std::vector<IRInst> exprNode = node->children[0].generate_ir();
    result.reserve(result.size() + exprNode.size());
    result.insert(result.end(), exprNode.begin(), exprNode.end());

    //Get if true block
    std::vector<IRInst> ifBlock = node->children[1].generate_ir();

    //Add logic to jump past if the condition is false
    IRInst jumpFalse;
    jumpFalse.type = IRInst::Relbfalse;
    jumpFalse.sourceReg = 0;
    jumpFalse.address = ifBlock.size() + (node->children.size() > 2 ? 2 : 1);
    result.push_back(jumpFalse);

    //If else block exists handle it
    if (node->children.size() == 3) {
        std::vector<IRInst> elseBlock = node->children[2].generate_ir();
        IRInst jumpElse;
        jumpElse.type = IRInst::Reljump;
        jumpElse.address = elseBlock.size() + 1;
        result.push_back(jumpElse);
    }

    return result;
}

std::vector<IRInst> ir_program(const ASTNode* node) {
    //Concat children
    std::vector<IRInst> result;

    std::vector<IRInst> childResult;
    for (const ASTNode& child : node->children) {
        childResult = child.generate_ir();
        result.reserve(result.size() + childResult.size());
        result.insert(result.end(), childResult.begin(), childResult.end());
    }

    return result;
}

std::vector<IRInst> ir_return(const ASTNode* node) {
    // ircode: return
    std::vector<IRInst> result;

    return result;
}

std::vector<IRInst> ir_symbol(const ASTNode* node) {
    // error (maybe)
    std::vector<IRInst> result;

    return result;
}

std::vector<IRInst> ir_while(const ASTNode* node) {
    // Like if
    std::vector<IRInst> result;

    return result;
}
