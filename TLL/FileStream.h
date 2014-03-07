#pragma once
#include "Stream.h"
#include <string>
#include <fstream>

namespace TLL {
	class FileStream : public Stream {
	public:
		FileStream(std::string& name);
		~FileStream();

		virtual StreamErrors Read(char* buf, int len);
		virtual StreamErrors Write(char* buf, int len);
		virtual void Close();

	private:
		std::fstream infile;
	};
}