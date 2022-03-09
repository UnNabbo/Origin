#pragma once

#include "Origin/Core/Core.h"

#include <stdint.h>

#include "Origin/Renderer/Primitives/Shader.h"
#include "Origin/Renderer/Primitives/VertexArray.h"



namespace Origin {
	template <class T>
	class ORIGIN_API AssetPool {
	public:
		static Reference<T> Load(const char* path, const Reference<T>& data);
		
		static Reference<T> Retrive(const char* path);

		static void Unload(const char* path);

		static bool Exist(const char* path);

		static void Clear();


	private:

		inline static std::unordered_map<const char*, Reference<T>> s_LoadedResources;
	};

	using ShaderAssetPool = AssetPool<Shader>;
	using VertexArrayAssetPool = AssetPool<VertexArray>;

}