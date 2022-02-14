#include "OGpch.h"

#include "ResourceManager.h"

namespace Origin {

	std::unordered_map<const char*, ResourceManager::FileData> ResourceManager::s_LoadedResources;

	void ResourceManager::Load(const char* path) {
		auto& Resource = s_LoadedResources.find(path);
		if (Resource != s_LoadedResources.end()) {
			s_LoadedResources[path].references++;
			return;
		}

		s_LoadedResources.insert({ path, {1, "napoli\0"} });
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

		int file_references = --s_LoadedResources[file].references;

		if (file_references <= 0)
			s_LoadedResources.erase(file);
	}
}
