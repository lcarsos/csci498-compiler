#include "ast.h"
#include "symboltable.h"

#include <climits>
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
static SymbolTable symT;

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
        default:
            return result;
    }
}

void ASTNode::print_ir(std::ostream& os) {
    std::vector<IRInst> fullIr = generate_ir();
    for(IRInst irnode : fullIr) {
        switch (irnode.type) {
            case IRInst::Mv:
                os << "mv R" << irnode.destReg << ", R" << irnode.sourceReg << std::endl;
                break;
            case IRInst::Memld:
                os << "memld R" << irnode.destReg << ", " << irnode.address << std::endl;
                break;
            case IRInst::Immld:
                os << "immld R" << irnode.destReg << ", " << irnode.number << std::endl;
                break;
            case IRInst::Memst:
                os << "memst R" << irnode.sourceReg << ", " << irnode.address << std::endl;
                break;
            case IRInst::Push:
                os << "push R" << irnode.sourceReg << std::endl;
                break;
            case IRInst::Mempush:
                os << "mempush " << irnode.address << std::endl;
                break;
            case IRInst::Immpush:
                os << "immpush " << irnode.number << std::endl;
                break;
            case IRInst::Pop:
                os << "pop R" << irnode.sourceReg << std::endl;
                break;
            case IRInst::Mempop:
                os << "mempop " << irnode.address << std::endl;
                break;
            case IRInst::Jump:
                os << "jump " << irnode.address << std::endl;
                break;
            case IRInst::BFalse:
                os << "bfalse " << irnode.address << ", R" << irnode.sourceReg << std::endl;
                break;
            case IRInst::BTrue:
                os << "btrue " << irnode.address << ", R" << irnode.sourceReg << std::endl;
                break;
            case IRInst::Bgt:
                os << "bgt " << irnode.address << ", R" << irnode.sourceReg <<
                    ", R" << irnode.destReg << std::endl;
                break;
            case IRInst::Bge:
                os << "bge " << irnode.address << ", R" << irnode.sourceReg <<
                    ", R" << irnode.destReg << std::endl;
                break;
            case IRInst::Beq:
                os << "beq " << irnode.address << ", R" << irnode.sourceReg <<
                    ", R" << irnode.destReg << std::endl;
                break;
            case IRInst::Bneq:
                os << "bneq " << irnode.address << ", R" << irnode.sourceReg <<
                    ", R" << irnode.destReg << std::endl;
                break;
            case IRInst::Blt:
                os << "blt " << irnode.address << ", R" << irnode.sourceReg <<
                    ", R" << irnode.destReg << std::endl;
                break;
            case IRInst::Ble:
                os << "ble " << irnode.address << ", R" << irnode.sourceReg <<
                    ", R" << irnode.destReg << std::endl;
                break;
            case IRInst::Reljump:
                os << "reljump " << irnode.number << std::endl;
                break;
            case IRInst::Relbfalse:
                os << "relbfalse " << irnode.number << ", R" << irnode.sourceReg << std::endl;
                break;
            case IRInst::Relbtrue:
                os << "relbtrue " << irnode.number << ", R" << irnode.sourceReg << std::endl;
                break;
            case IRInst::Relbgt:
                os << "relbgt " << irnode.number << ", R" << irnode.sourceReg <<
                    ", R" << irnode.destReg << std::endl;
                break;
            case IRInst::Relbge:
                os << "relbge " << irnode.number << ", R" << irnode.sourceReg <<
                    ", R" << irnode.destReg << std::endl;
                break;
            case IRInst::Relbeq:
                os << "relbeq " << irnode.number << ", R" << irnode.sourceReg <<
                    ", R" << irnode.destReg << std::endl;
                break;
            case IRInst::Relbneq:
                os << "relbneq " << irnode.number << ", R" << irnode.sourceReg <<
                    ", R" << irnode.destReg << std::endl;
                break;
            case IRInst::Relblt:
                os << "relblt " << irnode.number << ", R" << irnode.sourceReg <<
                    ", R" << irnode.destReg << std::endl;
                break;
            case IRInst::Relble:
                os << "relble " << irnode.number << ", R" << irnode.sourceReg <<
                    ", R" << irnode.destReg << std::endl;
                break;
            case IRInst::Call:
                os << "push PC" << std::endl << "jump " << irnode.address << std::endl;
                break;
            case IRInst::Return:
                os << "pop PC" << std::endl;
                break;
            case IRInst::Calc:
                os << "calc R" << irnode.destReg << ", " << irnode.nodeID << std::endl;
                break;
            default:
                break;
        }
    }
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

    //Get memory address to store to
    unsigned int mem = symT.retrieveSymbol(node->children[0].str).address;

    //Create new IRInst
    IRInst assignInst;
    assignInst.type = IRInst::Mempop;
    assignInst.address = mem;

    result.push_back(assignInst);

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
    std::vector<IRInst> result;
    std::vector<IRInst> childResult;

    bool symConst = node->children[0].isConst;
    std::string symType = node->children[0].str;

    for (size_t i = 1; i < node->children.size(); ++i) {
        if (node->children[i].type == ASTNode::Symbol) {
            //Just a basic dec. eg int x;
            //Add to symbol table
            symT.enterSymbol(SymbolTableEntry(node->children[i].str, symType, symConst));
        } else {
            //In assignment node, eg int x = 2 + 3;
            //The symbol is the first child, Add to symbol table
            symT.enterSymbol(SymbolTableEntry(node->children[i].children[0].str, symType, symConst));
            //and add assignment IR to result
            childResult = node->children[i].generate_ir();
            result.reserve(result.size() + childResult.size());
            result.insert(result.end(), childResult.begin(), childResult.end());
        }
    }

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

    IRInst pushToStack;
    pushToStack.type = IRInst::Push;
    pushToStack.sourceReg = 0;

    result.push_back(pushToStack);

    return result;
}

std::vector<IRInst> ir_if(const ASTNode* node) {
    std::vector<IRInst> result;

    //Calculate if expression, result will be in R0, and @SP
    std::vector<IRInst> exprNode = node->children[0].generate_ir();
    result.reserve(result.size() + exprNode.size());
    result.insert(result.end(), exprNode.begin(), exprNode.end());

    //Get if true block
    std::vector<IRInst> ifBlock = node->children[1].generate_ir();

    //Add logic to jump past if the condition is false
    IRInst jumpFalse;
    jumpFalse.type = IRInst::Relbfalse;
    jumpFalse.sourceReg = 0;
    jumpFalse.number = ifBlock.size() + (ifBlock.size() > 2 ? 2 : 1);
    result.push_back(jumpFalse);

    //If else block exists handle it
    if (node->children.size() == 3) {
        std::vector<IRInst> elseBlock = node->children[2].generate_ir();
        IRInst jumpElse;
        jumpElse.type = IRInst::Reljump;
        jumpElse.number = elseBlock.size() + 1;
        result.push_back(jumpElse);
    }

    return result;
}

std::vector<IRInst> ir_program(const ASTNode* node) {
    //Concat children
    std::vector<IRInst> result;

    symT.openScope();

    std::vector<IRInst> childResult;
    for (const ASTNode& child : node->children) {
        childResult = child.generate_ir();
        result.reserve(result.size() + childResult.size());
        result.insert(result.end(), childResult.begin(), childResult.end());
    }

    symT.closeScope();

    return result;
}

std::vector<IRInst> ir_return(const ASTNode* node) {
    // ircode: return
    std::vector<IRInst> result;

    if (node->children.size() > 0) {
        result = node->children[0].generate_ir();
    }

    IRInst retIR;
    retIR.type = IRInst::Return;
    result.push_back(retIR);

    return result;
}

std::vector<IRInst> ir_symbol(const ASTNode* node) {
    //This function should produce ir instructions to make either the immediate
    //or symbol be loaded onto the top of the stack, this should never be
    //called for declarations LHS node
    std::vector<IRInst> result;

    char* endPtr = 0;
    errno = 0;

    const long symbol_num = std::strtol(node->str.c_str(), &endPtr, 10);

    //Check if the conversion happend correctly
    if (endPtr == node->str.c_str() + node->str.size()) {
        if ((symbol_num == LONG_MIN || symbol_num == LONG_MAX) && errno == ERANGE) {
            //OUT OF RANGE ERROR
            return result;
        }

        if (sizeof(long) > sizeof(int)) { //have to coerce into an int, so making sure I won't overflow
            if (symbol_num > INT_MAX || symbol_num < INT_MIN) {
                //OUT OF INT RANGE ERROR
                return result;
            }
        }

        IRInst pushImm;
        pushImm.type = IRInst::Immpush;
        pushImm.number = static_cast<int>(symbol_num);

        result.push_back(pushImm);
        return result;
    }

    //Otherwise this is a symbol that should be in the symbol_table
    unsigned int mem = symT.retrieveSymbol(node->str).address;

    IRInst loadInst;
    loadInst.type = IRInst::Mempush;
    loadInst.address = mem;

    result.push_back(loadInst);

    return result;
}

std::vector<IRInst> ir_while(const ASTNode* node) {
    std::vector<IRInst> result;

    std::vector<IRInst> whileBlock = node->children[1].generate_ir();

    //Jump past the while block first
    IRInst doWhileJump;
    doWhileJump.type = IRInst::Reljump;
    doWhileJump.number = whileBlock.size() + 1;
    result.push_back(doWhileJump);

    //Add on the while block
    result.reserve(result.size() + whileBlock.size());
    result.insert(result.end(), whileBlock.begin(), whileBlock.end());

    //Calculate loop expression, result will be in R0, and @SP
    std::vector<IRInst> exprNode = node->children[0].generate_ir();
    result.reserve(result.size() + exprNode.size());
    result.insert(result.end(), exprNode.begin(), exprNode.end());

    //Jump back to beginning of the while block
    IRInst jumpBack;
    jumpBack.type = IRInst::Relbtrue;
    jumpBack.number = -1 * (result.size() - 1);

    result.push_back(jumpBack);

    return result;
}
