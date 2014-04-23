#include "datablock.h"

#include <string>

std::string DataBlock::getName(NameRef ref) {
    return dataStore.substr(ref.pos, ref.length);
}

std::string DataBlock::getDataBlock() const {
    return dataStore;
}

NameRef DataBlock::lookup(const char *name) {
    return lookup(std::string(name));
}

NameRef DataBlock::lookup(std::string name) {
    DataBlock::size_type pos = dataStore.find(name, 0);
    if (pos == std::string::npos) {
        // If it's not in there, add it!
        return insert(name);
    }
    return NameRef(pos, name.length());
}

DataBlock::size_type DataBlock::getSize() const {
    return dataStore.length();
}

// ***********
// * PRIVATE *
// ***********
NameRef DataBlock::insert(const char *name) {
    return insert(std::string(name));
}

NameRef DataBlock::insert(std::string name) {
    NameRef ref(dataStore.length(), name.length());
    dataStore.append(name);
    return ref;
}
