#include <string.h>
#include "datablock.h"

DataBlock::DataBlock():size(initialSize),length(0) {
    dataStore = new char[initialSize];
}

DataBlock::DataBlock(size_t initSize):size(initSize),length(0) {
    dataStore = new char[initSize];
}

DataBlock::~DataBlock() {
    delete[] dataStore;
}

std::string DataBlock::getName(NameRef ref) {
    std::string val = std::string(dataStore+ref.pos, ref.len);
    return val;
}

NameRef DataBlock::lookup(const char *name) {
    NameRef ref;
    char* found_ptr;

    //Search for the name, return a new ref to it if so
    if ((found_ptr = strstr(dataStore, name))) {
        ref.len = strlen(name);
        ref.pos = found_ptr - dataStore;
    }
    //Else add the name to the namespace
    else {
        ref = insert(name);
    }

    return ref;
}

NameRef DataBlock::lookup(std::string name) {
    return lookup(name.c_str());
}


/**********
 * PRIVATE
 */
void DataBlock::grow() {
    size_t newSize = size * 2 + 1;

    char *newStore = new char[newSize];
    memcpy(newStore, dataStore, size);
    delete[] dataStore;
    dataStore = newStore;
    size = newSize;

    // Set last byte to NULL
    dataStore[size] = '\0';
}

NameRef DataBlock::insert(const char *data) {
    NameRef ref;
    ref.pos = length;
    ref.len = strlen(data);

    // Grow the dataStore until we can fit the data
    while (ref.len + length >= size) grow();

    // Copy the data into the byte array
    memcpy(dataStore+length, data, ref.len);

    length += ref.len;

    return ref;
}

NameRef DataBlock::insert(std::string data) {
    return insert(data.c_str());
}
