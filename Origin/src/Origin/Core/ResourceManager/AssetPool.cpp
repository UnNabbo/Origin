#include "OGpch.h"

#include "AssetPool.h"

#include "Origin/Utility/Log/Log.h"


namespace Origin {

	template <typename T>
	Reference<T> AssetPool<T>::Load(const char* path, const Reference<T>& data) {
		if (Exist(path)) {
			return s_LoadedResources[path];
		}

		s_LoadedResources[path] = data;
		return data;
	}
	 
	template <typename T>
	Reference<T> AssetPool<T>::Retrive(const char* path) {

		if (Exist(path)) {
			return s_LoadedResources[path];
		}
		return nullptr;

	}

	template <typename T>
	void AssetPool<T>::Unload(const char* path) {
		auto& Resource = s_LoadedResources.find(path);
		if (!Exist(path))
			return;

		s_LoadedResources.erase(path);
		
	}

	template <typename T>
	void AssetPool<T>::Clear() {
		s_LoadedResources.clear();
	}

	template <typename T>
	bool AssetPool<T>::Exist(const char * path) {
		return s_LoadedResources.find(path) != s_LoadedResources.end();
	}

	template class AssetPool<Shader>;
	template class AssetPool<VertexArray>;

}
