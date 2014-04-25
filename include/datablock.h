#ifndef datablock_h
#define datablock_h

#include <string>

struct NameRef {
    size_t pos = 0;
    size_t len = 0;
    NameRef() {}
    NameRef(size_t pos, size_t len)
    : pos(pos), len(len) {}
};

class DataBlock {

public:
    DataBlock();
    DataBlock(size_t initSize);
    ~DataBlock();

    // get_name is a way of retrieving the string value stored at a location
    // in the namespace.
    std::string getName(NameRef ref);

    // Lookup checks if a name is in the namespace, returns that if so,
    //  otherwise adds to the table and then returns that.
    NameRef lookup(const char *data);
    NameRef lookup(const std::string& data);

#ifndef NDEBUG
    const char* getDatablock() const { return dataStore; }
    size_t getSize() const { return size; }
    size_t getLength() const { return length; }
#endif

private:
    char* dataStore;
    size_t size = INITIAL_SIZE;
    size_t length = 0;
    static const size_t INITIAL_SIZE = 20;

    void grow();
    NameRef insert(const char *data);
    NameRef insert(const std::string& data);
};

#endif
