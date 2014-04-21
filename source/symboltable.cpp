#include "symboltable.h"


SymbolTable::SymbolTable() {

}

void SymbolTable::openScope() {

}

void SymbolTable::closeScope() {

}

void SymbolTable::enterSymbol(string name, string type, vector<string>) {

}

bool SymbolTable::declaredLocally(string name) {
  // → bool /* accessible from current context */
  return false;
}

vector<string> SymbolTable::retrieveSymbol(string name) {
  // → attributes /* only when declaredLocally() → true */
  return vector<string>();
}
