#pragma once

#include "Origin/Core.h"

#include <string>
#include <unordered_map>

namespace Origin {
	class File {
	public:
		File(const char * path);
		~File();

		static File* Open(const char* path);
	private:
		static std::unordered_map<const char *, const char *> m_FileRead;
	};
};