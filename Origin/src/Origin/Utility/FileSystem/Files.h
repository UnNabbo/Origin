#pragma once

#include "Origin/Core.h"

namespace Origin {

	class FileStream;

	class ORIGIN_API File {
	public:
		static FileStream* Open(const char* path);
		static void Delete(const char* path);
		static void Move(const char* old_path, const char* new_path);
		static bool Exist(const char* path);
	};

	
}