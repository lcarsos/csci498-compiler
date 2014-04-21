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
    nameRef insert(const char *data);
    std::string get(nameRef ref);
#ifndef NDEBUG
    const char* getDatablock() const { return dataStore; }
    unsigned long getSize() const{ return size; }
    unsigned long getLength() const { return length; }
#endif

    private:
    void grow();
    char* dataStore;
    unsigned long size;
    unsigned long length;
    static const unsigned long initialSize = 20;
};

#endif
