#pragma once

#include "Origin/Core/Core.h"

namespace Origin {

	class FileStream;

	class ORIGIN_API File {
	public:
		static Reference<FileStream> Open(const char* path);
		static void Delete(const char* path);
		static void Move(const char* old_path, const char* new_path);
		static bool Exist(const char* path);
		static std::string GetName(const char* path);
	};

	
}