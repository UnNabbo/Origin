#include "OGpch.h"

#include "Origin/Renderer/Renderer.h"

#include "Platform/Opengl/OpenGLVertexArray.h"

namespace Origin {
	VertexArray* VertexArray::Create() {
		switch (Renderer::GetAPI()) {
			case RendererAPI::API::None:    ORIGIN_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:  return new OpenGLVertexArray();
		}

		ORIGIN_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}