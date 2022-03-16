#pragma once

#include "Origin/Renderer/Primitives/Buffers.h"

namespace Origin {

	class ORIGIN_API OpenGLVertexBuffer : public VertexBuffer{
	public:

		OpenGLVertexBuffer(uint32_t size);
		OpenGLVertexBuffer(float* data, uint32_t size);
		~OpenGLVertexBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void SetLayout(const BufferLayout& layout) override { m_Layout = layout; }
		virtual const BufferLayout& GetLayout() const override { return m_Layout; }


		virtual void SetData(const void* data, uint32_t size) override;
	private:
		uint32_t m_RendererID;
		uint32_t m_Size;
		BufferLayout m_Layout = {};
	};

	class ORIGIN_API OpenGLIndexBuffer : public IndexBuffer {
	public:

		OpenGLIndexBuffer(uint32_t size);
		OpenGLIndexBuffer(uint32_t* data, uint32_t size);
		~OpenGLIndexBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual uint32_t GetCount() const override { return m_Count; }
		
		virtual void SetData(uint32_t* data, uint32_t size) override;
	private:
		uint32_t m_RendererID;
		uint32_t m_Count;
	};
}