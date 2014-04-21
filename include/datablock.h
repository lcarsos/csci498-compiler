#ifndef __datablock_h__
#define __datablock_h__

#include <string>

struct nameRef {
    unsigned long pos, len;
};

class DataBlock {
    public:
    DataBlock();
    DataBlock(unsigned long initSize);
    ~DataBlock();

    // get_name is a way of retrieving the string value stored at a location 
    // in the namespace.
    std::string getName(nameRef ref);

    // Lookup checks if a name is in the namespace, returns that if so,
    //  otherwise adds to the table and then returns that.
    nameRef lookup(const char *data);
    nameRef lookup(std::string data);

#ifndef NDEBUG
    char* getDatablock() { return dataStore; }
    unsigned long getSize() { return size; }
    unsigned long getLength() { return length; }
#endif

    private:
    char* dataStore;
    unsigned long size;
    unsigned long length;
    static const unsigned long initialSize = 20;

    void grow();
    nameRef insert(const char *data);
    nameRef insert(std::string data);
};

#endif
