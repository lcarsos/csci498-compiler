#include <cassert>
#include <stdio.h>

#include "symboltable.h"

int main() {
    SymbolTable st1(0);
    SymbolTableNode *bad = st1.retrieveSymbol("a");
    assert(bad == 0);               /* Invalid symbols should not return a valid symbol node */
    // NOTE: Symbol table does not create an initial scope
    st1.openScope();
    bad = st1.retrieveSymbol("a");
    assert(bad == 0);               /* Invalid symbols should not return a valid symbol node */
    st1.enterSymbol("a", "string", {});
    SymbolTableNode* a = st1.retrieveSymbol("a");
    assert(a != 0);                 /* Make sure that enterSymbol works correctly */
    printf("made it here\n");
    assert(a->type == "string");    /* Test that retrieveSymbol returns the correct symbol */
    st1.openScope();
    st1.enterSymbol("x", "int", {});
    SymbolTableNode* hasx = st1.retrieveSymbol("x");
    assert(hasx != 0);              /* Make sure that enterSymbol works correctly inside scopes */
    assert(hasx->type == "int");    /* Test that retrieveSymbol returns the correct symbol */
    st1.closeScope();
    SymbolTableNode *stnode = st1.retrieveSymbol("x");
    assert(stnode == 0);            /* Test that closing the scope loses access to variables created within */
    SymbolTableNode *again = st1.retrieveSymbol("a");
    assert(again != 0);             /* Make sure that symbols survive across scopes */

    SymbolTable st2(0);
    st2.openScope();
    st2.enterSymbol("one", "int", {});
    st2.openScope();
    st2.enterSymbol("two", "int", {});
    st2.openScope();
    st2.enterSymbol("three", "int", {});
    SymbolTableNode *deep = st2.retrieveSymbol("one");
    assert(deep != 0);              /* Make sure "deeply" nested scopes maintain access to outer scopes */
    deep = st2.retrieveSymbol("two");
    assert(deep != 0);              /* Make sure access is maintained to outer scopes */
    deep = st2.retrieveSymbol("three");
    assert(deep != 0);              /* Make sure "deeply" nested scopes still allow symbol creation */
    st2.closeScope();
    assert(deep != 0);              /* TODO I'm not actually sure if this should be bad or not */
    deep = st2.retrieveSymbol("three");
    assert(deep == 0);              /* Make sure that the pointer actually changes when trying to get a bad pointer */
    deep = st2.retrieveSymbol("two");
    st2.closeScope();
    assert(deep != 0);              /* TODO I'm not actually sure if this should be bad or not */
    deep = st2.retrieveSymbol("two");
    assert(deep == 0);
    deep = st2.retrieveSymbol("one");
    assert(deep != 0);

    return 0;
}
