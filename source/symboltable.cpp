#include "symboltable.h"


SymbolTable::SymbolTable() {
  rootScope = new Scope(NULL);
  currentScope = rootScope;
}

void SymbolTable::openScope() {
  Scope *tmpScope = new Scope(currentScope);
  currentScope = tmpScope;
}

void SymbolTable::closeScope() {
  if (currentScope->getParent() != NULL) {
    currentScope = currentScope->getParent();
    delete currentScope;
  }
}

void SymbolTable::enterSymbol(string name, string type, map<string, string> attributes) {
  SymbolTableNode *tbnode = new SymbolTableNode({name, type, attributes});
  currentScope->addSymbolNode(tbnode);
}

bool SymbolTable::declaredLocally(string name) {
  return (currentScope->getNodeNamed(name) != NULL);
}

SymbolTableNode * SymbolTable::retrieveSymbolLocally(string name) {
  if (declaredLocally(name)) {
    return currentScope->getNodeNamed(name);
  }
  return NULL;
}

SymbolTableNode * SymbolTable::retrieveSymbol(string name) {
  Scope *searchScope = currentScope;
  while (searchScope->getParent() != NULL) {
    if (searchScope->getNodeNamed(name) != NULL) {
      return searchScope->getNodeNamed(name);
    }
    searchScope = searchScope->getParent();
  }
  return NULL;
}
