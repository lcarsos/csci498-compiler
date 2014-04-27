#include "symboltable.h"

#include <cassert>
#include <cstdio>

int main() {
    SymbolTable st1(0);
    SymbolTableNode *bad = st1.retrieveSymbol("a");
    // Invalid symbols should not return a valid symbol node
    assert(bad == nullptr);

    // NOTE: Symbol table does not create an initial scope
    st1.openScope();
    bad = st1.retrieveSymbol("a");
    // Invalid symbols should not return a valid symbol node
    assert(bad == nullptr);
    st1.enterSymbol("a", "string", {});

    SymbolTableNode* a = st1.retrieveSymbol("a");
    // Make sure that enterSymbol works correctly
    assert(a != nullptr);
    // Test that retrieveSymbol returns the correct symbol
    assert(a->type == "string");
    printf("Symbol table properly retrieves existing symbols.\n");


    st1.openScope();
    st1.enterSymbol("x", "int", {});
    SymbolTableNode* hasx = st1.retrieveSymbol("x");
    // Make sure that enterSymbol works correctly inside scopes
    assert(hasx != nullptr);
    // Test that retrieveSymbol returns the correct symbol
    assert(hasx->type == "int");
    st1.closeScope();

    SymbolTableNode *stnode = st1.retrieveSymbol("x");
    // Test that closing the scope loses access to variables created within
    assert(stnode == nullptr);
    SymbolTableNode *again = st1.retrieveSymbol("a");
    // Make sure that symbols survive across scopes
    assert(again != nullptr);

    SymbolTable st2(0);
    st2.openScope();
    st2.enterSymbol("one", "int", {});
    st2.openScope();
    st2.enterSymbol("two", "int", {});
    st2.openScope();
    st2.enterSymbol("three", "int", {});
    SymbolTableNode *deep = st2.retrieveSymbol("one");
    // Make sure "deeply" nested scopes maintain access to outer scopes
    assert(deep != nullptr);
    deep = st2.retrieveSymbol("two");
    // Make sure access is maintained to outer scopes
    assert(deep != nullptr);
    deep = st2.retrieveSymbol("three");
    // Make sure "deeply" nested scopes still allow symbol creation
    assert(deep != nullptr);
    st2.closeScope();
    // TODO I'm not actually sure if this should be bad or not
    assert(deep != nullptr);
    deep = st2.retrieveSymbol("three");
    // Make sure that the pointer actually changes when trying to get a bad pointer
    assert(deep == nullptr);
    deep = st2.retrieveSymbol("two");
    st2.closeScope();
    // TODO I'm not actually sure if this should be bad or not
    assert(deep != nullptr);
    deep = st2.retrieveSymbol("two");
    assert(deep == nullptr);
    deep = st2.retrieveSymbol("one");
    assert(deep != nullptr);

    return 0;
}
