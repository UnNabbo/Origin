#include "OGpch.h"

#include "Shader.h"
#include "Renderer.h"

#include "Origin/Utility/ResourceManager/AssetPool.h"
#include "Platform/Opengl/OpenGLShader.h"


namespace Origin {
	Shader* Shader::Create(const char* vertex_path, const char* fragment_path) {
		switch (Renderer::GetAPI()) {
		case RendererAPI::None:    ORIGIN_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::OpenGL:  		return new OpenGLShader(vertex_path, fragment_path);
		}

		ORIGIN_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}