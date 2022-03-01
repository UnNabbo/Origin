#pragma once

#include "Origin/Core/Core.h"

#include "Origin/Renderer/Primitives/VertexArray.h"


namespace Origin {
	class ORIGIN_API OpenGLVertexArray :  public VertexArray{
	public:
		OpenGLVertexArray();
		~OpenGLVertexArray();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void AddVertexBuffer(const AssetRef<VertexBuffer>& vertexBuffer) override;
		virtual void SetIndexBuffer(const AssetRef<IndexBuffer>& indexBuffer) override;

		virtual const std::vector<AssetRef<VertexBuffer>>& GetVertexBuffers() const override { return m_VertexBuffers; }
		virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffers() const override { return m_IndexBuffer; }

	private:
		uint32_t m_RendererID = 0;
		std::vector<AssetRef<VertexBuffer>> m_VertexBuffers;
		AssetRef<IndexBuffer> m_IndexBuffer;

	};
}


