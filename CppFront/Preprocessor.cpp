#include "Preprocessor.h"
#include "FileStream.h"
#include "MemoryStream.h"

using namespace Compiler;
using namespace std;

void Preprocessor::doPreproc(string& name){
	MemoryStream stream;
	doPreproc(name, stream);
}

void Preprocessor::doPreproc(string& name, Stream& output){
	FileStream file(name);
	doPreproc(file, output);
}

enum PreStates {
	TopLevel, SeenPound, InDirective, Include, InQuotes, InAngle, InComment
};

void Preprocessor::doPreproc(Stream& input, Stream& output){
	// ignore comments

	char buf[BUF_SIZE];
	input.Read(buf, BUF_SIZE);


}