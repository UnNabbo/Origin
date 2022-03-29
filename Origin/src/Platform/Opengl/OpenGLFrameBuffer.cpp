#include "OGpch.h"
#include "OpenGLFrameBuffer.h"

#include "glad/glad.h"

namespace Origin {
	static GLenum OriginAttachmentTypeToOpenGLAttachmentType(AttachmentType data) {
		switch (data) {
			case Origin::AttachmentType::Color: return GL_RGBA8;
			case Origin::AttachmentType::Depth: return GL_DEPTH24_STENCIL8;
		}
		ORIGIN_ASSERT(false, "");
		return 0;
	}

	static GLenum OriginAttachmentTypeToOpenGLAttachment(AttachmentType data) {
		switch (data) {
		case Origin::AttachmentType::Color: return GL_COLOR_ATTACHMENT0;
		case Origin::AttachmentType::Depth: return GL_DEPTH_ATTACHMENT;
		}
		ORIGIN_ASSERT(false, "");
		return 0;
	}

	OpenGLFrameBuffer::OpenGLFrameBuffer(const FrameBufferSpecification& spec) : m_Specification(spec){
		Build();
	}
	OpenGLFrameBuffer::~OpenGLFrameBuffer() {
		glDeleteFramebuffers(1, &m_RendererID);
		for (auto& attachment : m_Specification.Format) {
			glDeleteTextures(1,&attachment.AttachmentID);
		}

	}

	const FrameBufferSpecification& OpenGLFrameBuffer::GetSpecification() const {
		return m_Specification;
	}

	std::vector<Attachment>& OpenGLFrameBuffer::GetAttachments() {
		return m_Specification.Format.GetAttachments();
	}

	void OpenGLFrameBuffer::Resize(uint32_t width, uint32_t height) {
		m_Specification.Width = width;
		m_Specification.Height = height;
		Build();
	}

	void OpenGLFrameBuffer::Bind() const {
		glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
		glViewport(0, 0, m_Specification.Width, m_Specification.Height);
	}

	void OpenGLFrameBuffer::Unbind() const {
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void OpenGLFrameBuffer::Build() {
		glCreateFramebuffers(1, &m_RendererID);
		glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);

		for (auto& attachment : m_Specification.Format) {
			glCreateTextures(GL_TEXTURE_2D, 1, &attachment.AttachmentID);
			glBindTexture(GL_TEXTURE_2D, attachment.AttachmentID);
			glTexStorage2D(GL_TEXTURE_2D, 1, OriginAttachmentTypeToOpenGLAttachmentType(attachment.Type), m_Specification.Width, m_Specification.Height);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			if (attachment.Index >= 1 & attachment.Type != AttachmentType::Color) {
				continue;
			}
			glFramebufferTexture2D(GL_FRAMEBUFFER, OriginAttachmentTypeToOpenGLAttachment(attachment.Type) + attachment.Index, GL_TEXTURE_2D, attachment.AttachmentID, 0);
		}

		ORIGIN_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "FrameBuffer is Incomplete!");

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
}