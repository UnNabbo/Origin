#include "OGpch.h"

#include "Origin/Renderer/Renderer.h"

#include "Platform/Opengl/OpenGLShader.h"

namespace Origin {
	Shader* Shader::Create(const char* vertex_path, const char* fragment_path) {
		switch (Renderer::GetAPI()) {
		case RendererAPI::API::None:    ORIGIN_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  		return new OpenGLShader(vertex_path, fragment_path);
		}

		ORIGIN_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}