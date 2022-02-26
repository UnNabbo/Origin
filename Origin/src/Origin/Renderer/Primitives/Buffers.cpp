#include "OGpch.h"

#include "Origin/Renderer/Renderer.h"

#include "Platform/Opengl/OpenGLBuffers.h"

namespace Origin {
	VertexBuffer* VertexBuffer::Create() {
		switch (Renderer::GetAPI()) {
		case RendererAPI::API::None:    ORIGIN_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return new OpenGLVertexBuffer();
		}

		ORIGIN_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	VertexBuffer* VertexBuffer::Create(float* data, uint32_t size) {
		switch (Renderer::GetAPI()) {
		case RendererAPI::API::None:    ORIGIN_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return new OpenGLVertexBuffer(data, size);
		}

		ORIGIN_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create() {
		switch (Renderer::GetAPI()) {
		case RendererAPI::API::None:    ORIGIN_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return new OpenGLIndexBuffer();
		}

		ORIGIN_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* data, uint32_t size) {
		switch (Renderer::GetAPI()) {
		case RendererAPI::API::None:    ORIGIN_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return new OpenGLIndexBuffer(data, size);
		}

		ORIGIN_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}