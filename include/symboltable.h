#ifndef __symboltable_h__
#define __symboltable_h__

#include <iostream>
#include <string>
#include <map>

using namespace std;

struct SymbolTableNode {
  string name;
  string type;
  map<string, string> attributes;
};

class SymbolTable {
  class Scope {
    map<string, SymbolTableNode *> nodes; // symbol name => node
    Scope *parent;
  public:
    Scope(Scope *parent) : parent(parent) {};
    Scope * getParent() const { return parent; };
    SymbolTableNode * getNodeNamed(string name) const { return nodes.at(name); };
    void addSymbolNode(SymbolTableNode *node) { nodes[node->name] = node; };
  };

  Scope *rootScope;
  Scope *currentScope;

public:
  SymbolTable();

  void openScope();
  void closeScope();
  void enterSymbol(string name, string type, map<string, string> attributes);
  bool declaredLocally(string name);
  SymbolTableNode * retrieveSymbolLocally(string name);
  SymbolTableNode * retrieveSymbol(string name);

};

#endif
