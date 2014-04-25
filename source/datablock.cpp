#include <cstring>
#include <string>

#include "datablock.h"

DataBlock::DataBlock() {
    // The parentheses here are important!
    // Otherwise the new data isn't initialized.
    dataStore = new char[INITIAL_SIZE]();
}

DataBlock::DataBlock(size_t initSize)
: size(initSize) {
    // The parentheses here are important!
    // Otherwise the new data isn't initialized.
    dataStore = new char[initSize]();
}

DataBlock::~DataBlock() {
    delete[] dataStore;
    dataStore = nullptr;
}

std::string DataBlock::getName(NameRef ref) {
    // std::string's constructor expects a valid pointer.
    // TODO: Better error handling when dataStore is invalid.
    const char* ptr = &dataStore[ref.pos];
    if (ptr == nullptr) {
        return "(null)";
    }
    return std::string(ptr, ref.len);
}

NameRef DataBlock::lookup(const char *name) {
    // If name exists in dataStore, return a new NameRef to it.
    char* found_ptr = strstr(dataStore, name);
    if (found_ptr != nullptr) {
        return NameRef(strlen(name), found_ptr - dataStore);
    }
    // If it doesn't, add the name to the namespace.
    else {
        return insert(name);
    }
}

NameRef DataBlock::lookup(const std::string& name) {
    return lookup(name.c_str());
}


/***********
 * PRIVATE *
 ***********/
void DataBlock::grow() {
    size_t newSize = size * 2 + 1;

    char *newStore = new char[newSize];
    memcpy(newStore, dataStore, size);
    delete[] dataStore;

    dataStore = newStore;
    size = newSize;

    // Make sure dataStore is always NUL-terimated.
    dataStore[size-1] = '\0';
}

NameRef DataBlock::insert(const char *data) {
    NameRef ref(length, strlen(data));

    // Grow the dataStore until we can fit the data.
    // The `+ 1` accounts for the NUL-terminator.
    while (ref.len + length + 1 >= size) { grow(); }

    // Copy the data into the byte array.
    memcpy(&dataStore[length], data, ref.len);
    length += ref.len;

    // NUL-terimate just after the last insert.
    // Printing the store should always be valid.
    dataStore[length] = '\0';

    return ref;
}

NameRef DataBlock::insert(const std::string& data) {
    return insert(data.c_str());
}
