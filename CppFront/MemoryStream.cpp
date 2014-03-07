#include "MemoryStream.h"
#include <string.h>
#include <algorithm>

using namespace std;
using namespace Compiler;

MemoryStream::MemoryStream() {
	position = 0;
}

MemoryStream::~MemoryStream() {
}

void MemoryStream::Close(){
	buf.clear();
}

StreamErrors MemoryStream::Read(char* buf, int len){
	
	int readLen = min(position + len, (int) this->buf.size());

	memcpy(buf, &this->buf.begin() + position, readLen - position);
	position = readLen;

	if ((unsigned) position >= this->buf.size())
		return StreamErrors::EndOfFile;

	return StreamErrors::Ok;
}

StreamErrors MemoryStream::Write(char* buf, int len){
	this->buf.insert(this->buf.end(), buf, buf + len);
	return StreamErrors::Ok;
}
