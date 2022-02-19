#pragma once

#include "Origin/Core.h"

#include <stdint.h>

#include "Origin/Utility/FileSystem/Files.h"

namespace Origin {
	class ORIGIN_API ResourceManager {
	public:
		static void Load(const char* path, void * data);
		
		static void* Retrive(const char* path);

		static void Unload(const char* path);
	private:
		struct FileData {
			uint16_t references;
			void* data;
		};

		static std::unordered_map<const char*, FileData> s_LoadedResources;
	};
}