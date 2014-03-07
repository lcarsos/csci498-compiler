// C interface for backend
#pragma once
#include <string>

// filename should be a file containing binary TVM code
void __declspec(dllexport) Compile(char* filename);
void __declspec(dllexport) Compile(std::string& filename);