#include "OGpch.h"

#include "Origin/Renderer/Renderer.h"

#include "Platform/Opengl/OpenGLBuffers.h"

namespace Origin {
	Reference<VertexBuffer> VertexBuffer::Create() {
		switch (Renderer::GetAPI()) {
			case RendererAPI::API::None:    ORIGIN_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:  return MakeReference<OpenGLVertexBuffer>();
		}

		ORIGIN_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}


	Reference<VertexBuffer> VertexBuffer::Create(uint32_t size) {
		switch (Renderer::GetAPI()) {
		case RendererAPI::API::None:    ORIGIN_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return MakeReference<OpenGLVertexBuffer>(size);
		}

		ORIGIN_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	Reference<VertexBuffer> VertexBuffer::Create(float* data, uint32_t size) {
		switch (Renderer::GetAPI()) {
			case RendererAPI::API::None:    ORIGIN_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:  return MakeReference<OpenGLVertexBuffer>(data, size);
		}

		ORIGIN_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	Reference<IndexBuffer> IndexBuffer::Create() {
		switch (Renderer::GetAPI()) {
			case RendererAPI::API::None:    ORIGIN_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:  return MakeReference<OpenGLIndexBuffer>();
		}

		ORIGIN_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	Reference<IndexBuffer> IndexBuffer::Create(uint32_t size) {
		switch (Renderer::GetAPI()) {
		case RendererAPI::API::None:    ORIGIN_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return MakeReference<OpenGLIndexBuffer>(size);
		}

		ORIGIN_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	Reference<IndexBuffer> IndexBuffer::Create(uint32_t* data, uint32_t size) {
		switch (Renderer::GetAPI()) {
			case RendererAPI::API::None:    ORIGIN_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:  return MakeReference<OpenGLIndexBuffer>(data, size);
		}

		ORIGIN_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}