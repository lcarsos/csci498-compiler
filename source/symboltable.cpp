#include "symboltable.h"

using namespace std;

SymbolTable::SymbolTable(int base_address) {
    current_address = base_address;
    rootScope = new Scope(nullptr);
    currentScope = rootScope;
}

void SymbolTable::openScope() {
    Scope *tmpScope = new Scope(currentScope);
    currentScope = tmpScope;
}

void SymbolTable::closeScope() {
    if (currentScope->getParent() != nullptr) {
        currentScope = currentScope->getParent();
        delete currentScope;
  }
}

void SymbolTable::enterSymbol(string name, string type,
    map<string, string> attributes) {
    attributes["memory_address"] = current_address;
    if (type == "int") {
        current_address += 4;
    } else {
        current_address += 4;
    }
    SymbolTableNode *tbnode = new SymbolTableNode({name, type, attributes});
    currentScope->addSymbolNode(tbnode);
}

bool SymbolTable::declaredLocally(string name) {
    return (currentScope->getNodeNamed(name) != nullptr);
}

SymbolTableNode * SymbolTable::retrieveSymbolLocally(string name) {
    if (declaredLocally(name)) {
        return currentScope->getNodeNamed(name);
    }
    return nullptr;
}

SymbolTableNode * SymbolTable::retrieveSymbol(string name) {
    Scope *searchScope = currentScope;
    while (searchScope->getParent() != nullptr) {
        if (searchScope->getNodeNamed(name) != nullptr) {
            return searchScope->getNodeNamed(name);
        }
        searchScope = searchScope->getParent();
    }
    return nullptr;
}
