#ifndef datablock_h
#define datablock_h

#include <string>

class NameRef;

class DataBlock {
public:
    typedef std::string::size_type size_type;

    DataBlock()
    : dataStore() {}
	~DataBlock() {}

    // get_name is a way of retrieving the string value stored at a location
    // in the namespace.
    std::string getName(NameRef ref);
    std::string getDataBlock() const;

    // Lookup checks if a name is in the namespace, returns that if so,
    //  otherwise adds to the table and then returns that.
    NameRef lookup(const char *data);
    NameRef lookup(std::string data);

    size_type getSize() const;

private:
    std::string dataStore;

    NameRef insert(const char *data);
    NameRef insert(std::string data);
};

class NameRef {
public:
    NameRef(DataBlock::size_type pos, DataBlock::size_type length)
    : pos(pos), length(length) {}
    NameRef()
    : pos(0), length(0) {}

    DataBlock::size_type pos;
    DataBlock::size_type length;
};

#endif
