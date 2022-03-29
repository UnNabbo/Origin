#include "OGpch.h"

#include "Origin/Renderer/Renderer.h"

#include "FrameBuffer.h"
#include "Platform/Opengl/OpenGLFrameBuffer.h"


namespace Origin {

	Reference<FrameBuffer> FrameBuffer::Create(const FrameBufferSpecification& spec) {
		switch (Renderer::GetAPI()) {
			case RendererAPI::API::None:    ORIGIN_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:  return MakeReference<OpenGLFrameBuffer>(spec);
		}

		ORIGIN_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}