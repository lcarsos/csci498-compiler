#pragma once
#include "Stream.h"
#include <vector>

namespace TLL {
	class MemoryStream : public Stream {
	public:
		MemoryStream();
		~MemoryStream();

		virtual void Close();
		virtual StreamErrors Read(char* buf, int len);
		virtual StreamErrors Write(char* buf, int len);

	private:
		int position;
		std::vector<char> buf;
	};

}