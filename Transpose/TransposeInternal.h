#pragma once
#include <string>
#include "Stream.h"

namespace Transpose {
	class TransposeInternal {

	public:
		void Compile(std::string filename);
		void Compile(std::string& name, TLL::Stream& output);
		void Compile(TLL::Stream& input, TLL::Stream& output);

	private:
		TransposeInternal();
		~TransposeInternal();
	};
}