#include "OGpch.h"

#include "Origin/Renderer/Renderer.h"

#include "Platform/Opengl/OpenGLShader.h"

namespace Origin {
	AssetRef<Shader> Shader::Create(const char* vertex_path, const char* fragment_path) {
		ORIGIN_TRACE("{0}", sizeof(OpenGLShader));
		switch (Renderer::GetAPI()) {
			case RendererAPI::API::None:	ORIGIN_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:  return std::make_shared<OpenGLShader>(vertex_path, fragment_path);
		}

		ORIGIN_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	AssetRef<Shader> Shader::Create(const char* path) {
		ORIGIN_TRACE("{0}", sizeof(OpenGLShader));
		switch (Renderer::GetAPI()) {
		case RendererAPI::API::None:	ORIGIN_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return std::make_shared<OpenGLShader>(path);
		}

		ORIGIN_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}