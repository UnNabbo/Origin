#pragma once

#include "Origin/Core/Core.h"

#include "Origin/Renderer/Primitives/FrameBuffer.h"

namespace Origin {
	class ORIGIN_API OpenGLFrameBuffer : public FrameBuffer{
	public:
		OpenGLFrameBuffer(const FrameBufferSpecification& spec);
		virtual ~OpenGLFrameBuffer();

		virtual const FrameBufferSpecification& GetSpecification() const  override;
		virtual std::vector<Attachment>& GetAttachments() override;


		virtual void Resize(uint32_t width, uint32_t height) override;

		virtual void Bind() const override;
		virtual void Unbind() const override;

	private:
		void Build();

		uint32_t m_RendererID = 0;
		FrameBufferSpecification m_Specification;
	};
}