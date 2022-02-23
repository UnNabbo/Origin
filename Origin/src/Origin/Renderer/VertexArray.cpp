#include "OGpch.h"

#include "Renderer.h"

#include "VertexArray.h"

#include "Platform/Opengl/OpenGLVertexArray.h"

namespace Origin {
	VertexArray* VertexArray::Create() {
		switch (Renderer::GetAPI()) {
		case RendererAPI::None:    ORIGIN_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::OpenGL:  return new OpenGLVertexArray();
		}

		ORIGIN_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}