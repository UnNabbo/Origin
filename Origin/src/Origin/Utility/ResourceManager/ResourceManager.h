#pragma once

#include "Origin/Core.h"

#include <stdint.h>

namespace Origin {
	class ORIGIN_API ResourceManager {
	public:
		static void Load(const char* path);
		
		static void* Retrive(const char* path);

		static void Unload(const char* path);
	private:
		struct FileData {
			uint8_t references;
			void* data;
		};

		static std::unordered_map<const char*, FileData> s_LoadedResources;
	};
}