#pragma once

#include "Origin/Core/Core.h"

#include "Origin/Renderer/Primitives/Buffers.h"

namespace Origin {

	class ORIGIN_API VertexArray {
	public:
		virtual ~VertexArray() {}

		static Reference<VertexArray> Create(const char * name);

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void AddVertexBuffer(const Reference<VertexBuffer>& vertexBuffer) = 0;
		virtual void SetIndexBuffer(const Reference<IndexBuffer>& indexBuffer) = 0;

		virtual const std::vector<Reference<VertexBuffer>>& GetVertexBuffers() const = 0;
		virtual const Reference<IndexBuffer>& GetIndexBuffers() const = 0;

	};

}

