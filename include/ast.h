#ifndef AST_H
#define AST_H

#include <array>
#include <iostream>
#include <string>
#include <vector>
#include <map>

struct IRInst {
    IRInst() {}
    enum Type {
        Mv = 0,
        Memld,
        Immld,
        Memst, // sourceReg, address
        Push, // sourceReg
        Mempush, // address
        Immpush, // number
        Pop,
        Mempop, // address
        Jump,
        BFalse,
        BTrue,
        Bgt,
        Bge,
        Beq,
        Bneq,
        Blt,
        Ble,
        Reljump, // number
        Relbfalse, // sourceReg, number
        Relbtrue, //sourceReg, number
        Relbgt,
        Relbge,
        Relbeq,
        Relbneq,
        Relblt,
        Relble,
        Call,
        Return,
        Calc, // destReg, nodeID
        // New nodes that replace Calc
        Plus,
        Minus,
        Times,
        Divide,
        GT,
        GEQ,
        LT,
        LEQ,
        EQ,
        ShiftLeft,
        ShiftRight,
        Incr,
        Decr,
        Negate,
        Mod,
        BAND,
        BOR,
        BXOR,
        NOT,
        BNOT,
        AND,
        OR
    };
    IRInst::Type type;
    static unsigned int registerCount;
    static const size_t TOTAL_REGISTERS = 12;
    static const size_t TOTAL_WORK_REGISTERS = 3;
    static const size_t TOTAL_ALLOCATABLE_REGISTERS = TOTAL_REGISTERS-TOTAL_WORK_REGISTERS;
    unsigned int destReg = 0;
    unsigned int sourceReg = 0;
    unsigned int sourceReg2 = 0;
    unsigned int address = 0;
    unsigned int nodeID = 0;
    int number = 0;
};

class ASTNode {
public:
    // When adding to this, remember to adjust std::to_string in ast.cpp!
    enum Type {
        Empty = 0,
        Assignment,
        Block,
        Declarations,
        Expression,
        If,
        Program,
        Return,
        Symbol,
        While,
    };

    // This guarantees a unique number for every node created,
    //   but causes problems with copy constructors. There are
    //   over 200 nodes created before any of the final ones
    //   which we see in the tree are created!
    // TODO: Work around copy construtors creating false nodes.
    static int nodeCount;

    void addChild(const ASTNode& node);

    ASTNode::Type type;
    size_t uniqueID;

    // This is only used by Symbol.
    bool isConst;

    // Some nodes (e.g. int and float literals) need to save data, but not
    //   as strings.
    // TODO: More flexibility in type stored.
    std::string str;

    // TODO: Children should know about their parent.
    std::vector<ASTNode> children;

    ASTNode(Type type = Empty, std::string str = "")
    : type(type), isConst(false), str(str) {
        nodeCount += 1;
        uniqueID = nodeCount;
    }

    // Modifies a vector to add copies of all children, grand children, etc.
    //   The order is the result of a depth-first search.
    void find_all_children(std::vector<ASTNode>& nodes) const;

    // Prints the tree in accordance with Hellman's specification.
    void print_tree(std::ostream& os);

    //Generates IR code vector
    std::vector<IRInst> generate_ir() const;

    // Prints the IR code
    void print_ir(std::ostream& os);

    void makeConst();
};

std::string to_string(const ASTNode& node);
std::string to_string(ASTNode::Type type);

bool operator==(const ASTNode& a, const ASTNode& b);

#endif
