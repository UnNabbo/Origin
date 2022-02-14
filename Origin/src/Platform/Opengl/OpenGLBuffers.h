#pragma once

#include "Origin/Rendering/Buffers.h"

namespace Origin {

	class ORIGIN_API OpenGLVertexBuffer : public VertexBuffer{
	public:
		OpenGLVertexBuffer();
		~OpenGLVertexBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void SetData(float* data, uint32_t size) override;
	private:
		uint32_t m_RendererID;
	};

	class ORIGIN_API OpenGLIndexBuffer : public IndexBuffer {
	public:
		OpenGLIndexBuffer();
		~OpenGLIndexBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void SetData(uint32_t* data, uint32_t size) override;
	private:
		uint32_t m_RendererID;
	};
}