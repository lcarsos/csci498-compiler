#include "pch.h"
#include "Transpose.h"
#include "FileStream.h"

using namespace TLL;
using namespace std;

void Compile(char* filename){
	Compile(string(filename));
}

void Compile(string& filename){
	FileStream file(filename);
	file.Close();
}