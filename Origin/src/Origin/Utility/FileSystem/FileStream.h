#pragma once

#include "Origin/Core/Core.h"

#include "Files.h"

namespace Origin {
	class ORIGIN_API FileStream {
	public:

		virtual ~FileStream() = default;

		static Reference<FileStream> Create(const char *path);

		virtual std::string& Read() = 0;
		virtual std::string& GetPath() = 0;
	};
}
