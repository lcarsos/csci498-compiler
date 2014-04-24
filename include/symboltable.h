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
  class Scope {
    std::map<std::string, SymbolTableNode *> nodes; // symbol name => node
    Scope *parent;
  public:
    Scope(Scope *parent) : parent(parent) {};
    Scope * getParent() const { return parent; };
    SymbolTableNode * getNodeNamed(std::string name) const { return nodes.at(name); };
    void addSymbolNode(SymbolTableNode *node) { nodes[node->name] = node; };
  };

  Scope *rootScope;
  Scope *currentScope;

public:
  SymbolTable();

  void openScope();
  void closeScope();
  void enterSymbol(std::string name, std::string type, std::map<std::string, std::string> attributes);
  bool declaredLocally(std::string name);
  SymbolTableNode * retrieveSymbolLocally(std::string name);
  SymbolTableNode * retrieveSymbol(std::string name);

};

#endif
