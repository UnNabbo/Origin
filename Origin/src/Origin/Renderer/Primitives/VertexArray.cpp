#include "OGpch.h"

#include "Origin/Renderer/Renderer.h"

#include "Platform/Opengl/OpenGLVertexArray.h"

#include "Origin/Core/ResourceManager/AssetPool.h"


namespace Origin {
	Reference<VertexArray> VertexArray::Create(const char * name) {
		switch (Renderer::GetAPI()) {
			case RendererAPI::API::None:    ORIGIN_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:  return VertexArrayAssetPool::Load(name, std::make_shared<OpenGLVertexArray>());
		}

		ORIGIN_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}