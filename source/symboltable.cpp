#include "symboltable.h"

#include <algorithm>
#include <iomanip>
#include <ostream>
#include <sstream>
#include <string>
#include <utility>

// SymbolTableEntry
void SymbolTableEntry::setInitialized() {
    initialized = true;
}

// LocalSymbolTable

bool LocalSymbolTable::enterSymbol(const SymbolTableEntry& entry) {
    if (entries.find(entry.name) != entries.end()) {
        // It already exists, raise a redefinition error.
        return false;
    }
    entries.insert(std::make_pair(entry.name, entry));
    return true;
}

bool LocalSymbolTable::declared(const std::string& name) const {
    return entries.find(name) != entries.end();
}

SymbolTableEntry LocalSymbolTable::retrieveSymbol(const std::string& name) {
    return retrieveSymbolRef(name);
}

void LocalSymbolTable::setInitialized(const std::string& name) {
    retrieveSymbolRef(name).setInitialized();
}

int LocalSymbolTable::getParentIndex() const {
    return parentIndex;
}

const LocalSymbolTable::Entries_t& LocalSymbolTable::getEntries() const {
    return entries;
}

SymbolTableEntry& LocalSymbolTable::retrieveSymbolRef(const std::string& name) {
    if (!declared(name)) {
        // TODO: Handle error: Not symbol delcared.
    }
    return entries.at(name);
}

LocalSymbolTable& LocalSymbolTable::operator= (const LocalSymbolTable& other) {
    if (*this != other) {
        entries = other.entries;
        parentIndex = other.parentIndex;
    }
    return *this;
}

// SymbolTable
void SymbolTable::openScope() {
    LocalSymbolTable ltable(next_memory_address);
    if (!scopes.empty()) {
        // We have a scope to use as the parent.
        ltable = LocalSymbolTable(current_scope, next_memory_address);
    }
    scopes.push_back(ltable);
    current_scope = scopes.size() - 1;
}

void SymbolTable::closeScope() {
    next_memory_address = scopes[current_scope].getBaseAddress();
    current_scope = scopes[current_scope].getParentIndex();
}

bool SymbolTable::hasOpenScope() const {
    return scopes.empty();
}

bool SymbolTable::enterSymbol(SymbolTableEntry entry) {
    if (!hasOpenScope()) {
        // TODO: Handle error: No scopes open yet.
    }
    //Assigns the symbol the next available address
    entry.address = next_memory_address;
    next_memory_address += 4;

    return scopes[current_scope].enterSymbol(entry);
}

bool SymbolTable::declaredLocally(const std::string& name) const {
    if (!hasOpenScope()) {
        // TODO: Handle error: No scopes open yet.
    }
    return scopes[current_scope].declared(name);
}

bool SymbolTable::declared(const std::string& name) const {
    bool found = false;
    for (auto scope : scopes) {
        if (scope.declared(name)) {
            if (found) {
                // Conflict! What do we do!?
            } else {
                found = true;
            }
        }
    }
    return found;
}

SymbolTableEntry SymbolTable::retrieveSymbolLocally(const std::string& name) {
    return scopes[current_scope].retrieveSymbol(name);
}

SymbolTableEntry SymbolTable::retrieveSymbol(const std::string& name) {
    return retrieveSymbolRef(name);
    // TODO: Handle error: Not declared
    // return SymbolTableEntry("ERROR", "ERROR");
}

void SymbolTable::setInitialized(const std::string& name) {
    retrieveSymbolRef(name).setInitialized();
}

void SymbolTable::pretty_print(std::ostream& os) const {
    // Pretty print the table. Everything should fit within
    //   80 characters. There's a lot of magic numbers here.
    //   Sorry.

    for (unsigned int i = 0; i < scopes.size(); i += 1) {
        os << "Scope: "  << std::left << std::setw(3) << i;
        os << "Parent: " << std::left << std::setw(3);
        os << scopes[i].getParentIndex();
        os << std::endl;

        for (int i = 0; i < 77; i += 1) {
            os << '~';
        }
        os << std::endl;
        os << "| Name                  | ";
        os << "Type                    | ";
        os << "Address                 |";
        os << std::endl;

        for (int i = 0; i < 77; i += 1) {
            os << '~';
        }
        os << std::endl;

        for (auto pair : scopes[i].getEntries()) {
            auto name = pair.second.name;
            auto type = pair.second.type;
            auto address = pair.second.address;

            os << "| ";
            os << std::setw(24) << name;
            os << std::setw(26) << type;
            os << std::setw(23) << address << " |";
            os << std::endl;
        }

        for (int i = 0; i < 77; i += 1) {
            os << '-';
        }

        os << std::endl;
        os << std::endl;
    }
}

SymbolTableEntry& SymbolTable::retrieveSymbolRef(const std::string& name) {
    if (declared(name)) {
        int i = current_scope;
        while (!scopes[i].declared(name)) {
            i = scopes[i].getParentIndex();
        }
        return scopes[i].retrieveSymbolRef(name);
    }
    // TODO: Handle error: Not declared
    // return SymbolTableEntry("ERROR", "ERROR");
}

// Nonmember Functions

bool operator== (const SymbolTableEntry& a, const SymbolTableEntry& b) {
    return a.name == b.name
        && a.type == b.type
        && a.address == b.address;
    // Add additional attributes as necessary.
}

bool operator!= (const SymbolTableEntry& a, const SymbolTableEntry& b) {
    return !(a == b);
}

bool operator== (const LocalSymbolTable& a, const LocalSymbolTable& b) {
    return a.entries == b.entries
        && a.parentIndex == b.parentIndex;
}

bool operator!= (const LocalSymbolTable& a, const LocalSymbolTable& b) {
    return !(a == b);
}

std::string to_string(const SymbolTableEntry& entry) {
    std::stringstream ss;
    ss << "[name=\"" << entry.name << "\", type=\"" << entry.type
        << "\"]";
    return ss.str();
}
