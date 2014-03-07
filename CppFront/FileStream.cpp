#include "FileStream.h"
#include <fstream>

using namespace Compiler;
using namespace std;

FileStream::FileStream(string& name) : infile(name) {

}


FileStream::~FileStream() {
}

void FileStream::Close(){
	infile.close();
}

StreamErrors FileStream::Read(char* buf, int len){
	infile.read(buf, len);

	if (infile.gcount() != len)
		return StreamErrors::EndOfFile;

	return StreamErrors::Ok;
}

StreamErrors FileStream::Write(char* buf, int len){
	infile.write(buf, len); 
	return StreamErrors::Ok;
}