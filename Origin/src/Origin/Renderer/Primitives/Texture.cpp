#include "OGpch.h"

#include "Texture.h"

#include "Origin/Renderer/Renderer.h"

#include "Platform/Opengl/OpenGLTexture2D.h"


namespace Origin {

	Reference<Texture2D> Texture2D::Create(const std::string& path) {
		switch (Renderer::GetAPI()) {
			case RendererAPI::API::None:    ORIGIN_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:  return std::make_shared<OpenGLTexture2D>(path);
		}

		ORIGIN_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}


}