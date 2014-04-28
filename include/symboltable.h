#ifndef symboltable_h
#define symboltable_h

#include <ostream>
#include <string>
#include <unordered_map>
#include <vector>

struct SymbolTableEntry {
    std::string name;
    std::string type;
    bool isConst;
    // An address of 0 is never valid.
    unsigned int address = 0;

    // Add additional attributes as necessary.
    // Do not forget to update operator== in symboltable.cpp!

    SymbolTableEntry(std::string name, std::string type)
    : name(name), type(type), isConst(false) {}

    SymbolTableEntry(std::string name, std::string type, bool constant)
    : name(name), type(type), isConst(constant) {}
};

class LocalSymbolTable {
public:
    // Long typename is long.
    typedef std::unordered_map<std::string, SymbolTableEntry> Entries_t;

    // Return false when the symbol already exists.
    bool enterSymbol(const SymbolTableEntry& entry);
    bool declared(const std::string& name) const;

    SymbolTableEntry retrieveSymbol(const std::string& name) const;

    int getParentIndex() const;
    const Entries_t& getEntries() const;

    LocalSymbolTable() {}
    explicit LocalSymbolTable(int parentIndex)
    : parentIndex(parentIndex) {}

    LocalSymbolTable& operator= (const LocalSymbolTable& other);

    friend bool operator== (const LocalSymbolTable& a,
                            const LocalSymbolTable& b);
    friend bool operator!= (const LocalSymbolTable& a,
                            const LocalSymbolTable& b);

private:
    Entries_t entries;

    // The index of its parent in the scopes-vector in SymbolTable.
    int parentIndex = 0;
};

class SymbolTable {
public:
    void openScope();
    void closeScope();

    bool hasOpenScope() const;

    // Return false when the symbol already exists in the local scope.
    bool enterSymbol(SymbolTableEntry entry);

    bool declaredLocally(const std::string& name) const;
    bool declared(const std::string& name) const;

    SymbolTableEntry retrieveSymbolLocally(const std::string& name) const;
    SymbolTableEntry retrieveSymbol(const std::string& name) const;

    void pretty_print(std::ostream& os) const;

private:
    // Long typename is long.
    typedef std::unordered_map<std::string, SymbolTableEntry> Entries_t;

    Entries_t entries;
    std::vector<LocalSymbolTable> scopes;
    // index of current scope in scopes.
    unsigned int current_scope = 0;
    unsigned int next_memory_address = 4;

};

bool operator== (const SymbolTableEntry& a, const SymbolTableEntry& b);
bool operator!= (const SymbolTableEntry& a, const SymbolTableEntry& b);

bool operator== (const LocalSymbolTable& a, const LocalSymbolTable& b);
bool operator!= (const LocalSymbolTable& a, const LocalSymbolTable& b);


std::string to_string(const SymbolTableEntry& entry);

#endif
