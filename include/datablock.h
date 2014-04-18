#ifndef __datablock_h__
#define __datablock_h__

class DataBlock {
    public:
    DataBlock();
    DataBlock(unsigned long initSize);
    ~DataBlock();
    char* insert(const char *data);

    private:
    void grow();
    char* dataStore;
    unsigned long size;
    unsigned long length;
    const unsigned long initialSize = 20;
};

#endif
