#include "OGpch.h"

#include "ResourceManager.h"

#include "Origin/Utility/Log/Log.h"

namespace Origin {

	std::unordered_map<const char*, ResourceManager::FileData> ResourceManager::s_LoadedResources;

	void ResourceManager::Load(const char* path, void* data) {
		auto& Resource = s_LoadedResources.find(path);
		if (Resource != s_LoadedResources.end()) {
			s_LoadedResources[path].references++;
			return;
		}

		void* heap_data = new void*;
		std::memcpy(heap_data, data, sizeof(data));
		s_LoadedResources.insert({ path, {1,  heap_data} });
	}

	void* ResourceManager::Retrive(const char* path) {
		auto& Resource = s_LoadedResources.find(path);
		if (Resource != s_LoadedResources.end()) {
			return s_LoadedResources[path].data;
		}
		return nullptr;

	}

	void ResourceManager::Unload(const char* file) {
		auto& Resource = s_LoadedResources.find(file);
		if (Resource == s_LoadedResources.end())
			return;

		auto& file_reference = s_LoadedResources[file];

		if (--file_reference.references <= 0) {
			s_LoadedResources.erase(file);
			delete file_reference.data;
		}
	}
}
