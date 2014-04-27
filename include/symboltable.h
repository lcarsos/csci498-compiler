#ifndef symboltable_h
#define symboltable_h

#include <iostream>
#include <string>
#include <map>

struct SymbolTableNode {
    std::string name;
    std::string type;
    std::map<std::string, std::string> attributes;
};

class SymbolTable {
    int current_address;

    class Scope {
        // symbol name => node
        std::map<std::string, SymbolTableNode*> nodes;
        Scope *parent = nullptr;

    public:
        Scope(Scope *parent) : parent(parent) { };

        Scope* getParent() const {
            return parent;
        };

        SymbolTableNode* getNodeNamed(const std::string& name) const {
            return nodes.at(name);
        };

        void addSymbolNode(SymbolTableNode *node) {
            if (node != nullptr) {
                nodes[node->name] = node;
            }
        };
    };

    Scope *rootScope = nullptr;
    Scope *currentScope = nullptr;

public:
    SymbolTable(int base_address);

    void openScope();
    void closeScope();
    void enterSymbol(std::string name, std::string type,
        std::map<std::string, std::string> attributes);
    bool declaredLocally(std::string name);

    // DO NOT free the pointers retrieved from here
    // These are pointers to the internal representation
    SymbolTableNode* retrieveSymbolLocally(std::string name);
    SymbolTableNode* retrieveSymbol(std::string name);

};

#endif
