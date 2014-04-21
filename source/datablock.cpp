#include <string.h>
#include "datablock.h"

DataBlock::DataBlock():size(initialSize),length(0) {
    dataStore = new char[initialSize];
}

DataBlock::DataBlock(unsigned long initSize):size(initSize),length(0) {
    dataStore = new char[initSize];
}

DataBlock::~DataBlock() {
    delete[] dataStore;
}

nameRef DataBlock::insert(const char *data) {
    nameRef ref;
    ref.pos = length;
    ref.len = strlen(data);

    // Grow the dataStore until we can fit the data
    while (ref.len + length >= size) {
        grow();
    }

    // Copy the data into the byte array
    memcpy(dataStore+length, data, ref.len);

    length += ref.len;

    return ref;
}

std::string DataBlock::get(nameRef ref) {
    std::string val = std::string(dataStore+ref.pos, ref.len);
    return val;
}

void DataBlock::grow() {
    unsigned long newSize = size * 2 + 1;

    char *newStore = new char[newSize];
    memcpy(newStore, dataStore, size);
    delete[] dataStore;
    dataStore = newStore;
    size = newSize;

    // Set last byte to NULL
    dataStore[size] = '\0';
}
