#include "pch.h"
#include "TransposeInternal.h"
#include "MemoryStream.h"
#include "FileStream.h"

using namespace Transpose;
using namespace TLL;
using namespace std;

TransposeInternal::TransposeInternal() {
}


TransposeInternal::~TransposeInternal() {
}

void TransposeInternal::Compile(string filename){
	MemoryStream stream;
	Compile(filename, stream);
}

void TransposeInternal::Compile(string& name, Stream& output){
	FileStream file(name);
	Compile(file, output);
}

void TransposeInternal::Compile(Stream& input, Stream& output){

}