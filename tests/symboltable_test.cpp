#include <cassert>
#include <stdio.h>

#include "symboltable.h"

#include <iostream>
#include <string>
#include <vector>

// Our version is not in std and the confusion of having nonconflicting
//    overloads in different namespaces is too much for me.
using std::to_string;

int test_total = 0;
int test_fails = 0;

void test_SymbolTable_insert(SymbolTable& table, SymbolTableEntry entry) {
    test_total += 1;
    if (!table.enterSymbol(entry)) {
        test_fails += 1;
        std::cerr << "[" << test_total << "] Entry \n\t" << to_string(entry);
        std::cerr << "\n was not properly inserted." << std::endl;
        std::cerr << std::endl;
    }
}

void test_SymbolTable_entry_exists(SymbolTable& table, SymbolTableEntry entry) {
    test_total += 1;
    auto retrieved = table.retrieveSymbol(entry.name);
    if (retrieved != entry) {
        test_fails += 1;
        std::cerr << "[" << test_total << "] Expected \n\t";
        std::cerr << to_string(entry) << ",\n but instead";
        std::cerr << " table gave us \n\t" << to_string(retrieved) << ".";
        std::cerr << std::endl << std::endl;
    }
}

void print_test_results() {
    std::cout << "=====TEST RESULTS=====" << std::endl;
    std::cout << test_fails << "/" << test_total << " failures" << std::endl;
}

// Easy way to get unique entries to insert without having to work for it.
SymbolTableEntry lazy_new_entry() {
    static int count = 1;

    std::string name = "entry_" + to_string(count);
    count += 1;
    return SymbolTableEntry(name, "TestType");
}

int main() {
    SymbolTable table;

    const int ENTRY_COUNT = 4;
    std::vector<SymbolTableEntry> entries;
    for (int i = 0; i < ENTRY_COUNT; i += 1) {
        entries.push_back(lazy_new_entry());
    }

    for (auto entry : entries) {
        table.openScope();
        test_SymbolTable_insert(table, entry);
        test_SymbolTable_entry_exists(table, entry);
    }

    // Lookup should still work when we nest deeper.
    table.openScope();
    for (auto entry : entries) {
        test_SymbolTable_entry_exists(table, entry);
    }

    // Does shadowing work?
    table.openScope();
    for (auto entry : entries) {
        auto old = entry;
        entry.type = "ShadowTestType";

        test_SymbolTable_insert(table, entry);
        test_SymbolTable_entry_exists(table, entry);
    }

    print_test_results();
    std::cout << "=====SYMBOL TABLE=====" << std::endl;
    table.pretty_print(std::cout);

    return 0;
}
