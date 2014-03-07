#pragma once
#include <string>
#include "Stream.h"

namespace Compiler {
	class Preprocessor {
	public:
		
		const static int BUF_SIZE = 1024;
		void doPreproc(std::string& name);
		void doPreproc(std::string& name, Stream& output);
		void doPreproc(Stream& input, Stream& output);

	private:
		Preprocessor(){};
	};
}