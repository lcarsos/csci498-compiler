#ifndef __symboltable_h__
#define __symboltable_h__

#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct SymbolTableNode {
  string name;
  string type;
  vector<string> attributes;
  int scope;
};

class SymbolTable {

public:
  SymbolTable();

  void openScope();
  void closeScope();
  void enterSymbol(string name, string type, vector<string> attributes);
  bool declaredLocally(string name);
  vector<string> retrieveSymbol(string name);

};

#endif
