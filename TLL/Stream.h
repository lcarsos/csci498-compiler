#pragma once

namespace TLL {

	enum StreamErrors {
		Ok, NullBuf, StreamClosed, OutOfBounds, EndOfFile
	};


	class Stream {
	public:
		Stream();
		~Stream();

		virtual StreamErrors Read(char* buf, int len) = 0;
		virtual StreamErrors Write(char* buf, int len) = 0;
		virtual void Close() = 0;
	};
}