#include "OGpch.h"

#include "Buffers.h"

#include "Platform/Opengl/OpenGLBuffers.h"

namespace Origin {
	VertexBuffer* VertexBuffer::Create() {
		return new OpenGLVertexBuffer();
	}

	IndexBuffer* IndexBuffer::Create() {
		return new OpenGLIndexBuffer();
	}

}