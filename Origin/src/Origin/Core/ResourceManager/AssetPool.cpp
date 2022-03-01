#include "OGpch.h"

#include "AssetPool.h"

#include "Origin/Utility/Log/Log.h"

namespace Origin {

	std::unordered_map<const char*, AssetPool::FileData> AssetPool::s_LoadedResources;

	void AssetPool::Load(const char* path, void* data) {
		auto& Resource = s_LoadedResources.find(path);
		if (Resource != s_LoadedResources.end()) {
			s_LoadedResources[path].references++;
			return;
		}

		s_LoadedResources.insert({ path, {1,  data} });
	}

	void* AssetPool::Retrive(const char* path) {

		auto& Resource = s_LoadedResources.find(path);
		if (Resource != s_LoadedResources.end()) {
			s_LoadedResources[path].references++;
			return s_LoadedResources[path].data;
		}
		return nullptr;

	}

	void AssetPool::Unload(const char* file) {
		auto& Resource = s_LoadedResources.find(file);
		if (Resource == s_LoadedResources.end())
			return;

		auto data = s_LoadedResources[file];
		if (--data.references <= 0) {
			s_LoadedResources.erase(file);
			delete data.data;
		}
		
	}

	void AssetPool::Clear() {
		for (auto& pair : s_LoadedResources) {
			delete pair.second.data;
		}
		s_LoadedResources.clear();
	}
}
