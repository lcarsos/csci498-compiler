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

char* DataBlock::insert(const char *data) {
    size_t data_size = strlen(data);

    /* Grow the dataStore until we can fit the data */
    while (data_size + length > size) {
        grow();
    }

    /* Copy the data into the byte array */
    char *start = dataStore+length;
    memcpy(start, data, data_size);

    length += data_size;

    return start;
}

void DataBlock::grow() {
    unsigned long newSize = size * 2 + 1;

    char *newStore = new char[newSize];
    memcpy(newStore, dataStore, size);
    delete[] dataStore;
    dataStore = newStore;
    size = newSize;
}
