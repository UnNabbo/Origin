#pragma once

#include "Origin/Core/Core.h"

#include "Origin/Renderer/Primitives/Buffers.h"


namespace Origin {

	class ORIGIN_API VertexArray {
	public:
		virtual ~VertexArray() {}

		static AssetRef<VertexArray> Create();

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void AddVertexBuffer(const AssetRef<VertexBuffer>& vertexBuffer) = 0;
		virtual void SetIndexBuffer(const AssetRef<IndexBuffer>& indexBuffer) = 0;

		virtual const std::vector<AssetRef<VertexBuffer>>& GetVertexBuffers() const = 0;
		virtual const AssetRef<IndexBuffer>& GetIndexBuffers() const = 0;

	};

}

