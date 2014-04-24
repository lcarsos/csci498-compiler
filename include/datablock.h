#ifndef datablock_h
#define datablock_h

#include <string>

struct NameRef {
    size_t pos, len;
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
    NameRef lookup(std::string data);

#ifndef NDEBUG
    const char* getDatablock() const { return dataStore; }
    size_t getSize() const { return size; }
    size_t getLength() const { return length; }
#endif

    private:
    char* dataStore;
    size_t size;
    size_t length;
    static const size_t initialSize = 20;

    void grow();
    NameRef insert(const char *data);
    NameRef insert(std::string data);
};

#endif
