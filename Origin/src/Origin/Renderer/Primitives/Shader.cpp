#include "OGpch.h"

#include "Origin/Renderer/Renderer.h"

#include "Platform/Opengl/OpenGLShader.h"
#include "Origin/Core/ResourceManager/AssetPool.h"

namespace Origin {
	Reference<Shader> Shader::Create(const char * name, const char* vertex_path, const char* fragment_path) {
		switch (Renderer::GetAPI()) {
			case RendererAPI::API::None:	ORIGIN_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:  return std::make_shared<OpenGLShader>(name, vertex_path, fragment_path);
		}

		ORIGIN_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	Reference<Shader> Shader::Create(const char* path) {
		switch (Renderer::GetAPI()) {
		case RendererAPI::API::None:	ORIGIN_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return ShaderAssetPool::Load(path, std::make_shared<OpenGLShader>(path));
		}

		ORIGIN_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}