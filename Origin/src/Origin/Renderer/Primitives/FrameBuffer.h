#pragma once

#include "Origin/Core/Core.h"

namespace Origin {

	enum class AttachmentType {
		Color, Depth,
	};

	struct Attachment {
		AttachmentType Type;
		std::string Name;
		uint32_t Index;
		uint32_t AttachmentID;

		Attachment(AttachmentType type, std::string name = "NONE", uint32_t index = 0) : Type(type), Name(name), Index(index){}
	};

	class FrameBufferFormat {
	public:
		FrameBufferFormat(const std::initializer_list<Attachment>& attachments) : m_Attachments(attachments), m_Size(m_Attachments.size()) { Validate(); }

		inline std::vector<Attachment>& GetAttachments() { return m_Attachments; }
		inline const uint32_t& GetSize() const { return m_Size; }


		std::vector<Attachment>::iterator begin() { return m_Attachments.begin(); }
		std::vector<Attachment>::iterator end() { return m_Attachments.end(); }
	private:
		void Validate() {
			uint32_t ColorAttachmentCount = 0, DepthAttachmentCount = 0;
			for (auto& attachment : m_Attachments) {
				switch (attachment.Type) {
				case Origin::AttachmentType::Color:
					ColorAttachmentCount++;
					break;
				case Origin::AttachmentType::Depth:
					DepthAttachmentCount++;
					break;
				}
			}
			if (ColorAttachmentCount > 32 || DepthAttachmentCount > 1) {
				ORIGIN_ASSERT(false, "Invalid FrameBuffer Format")
			}
		}

		std::vector<Attachment> m_Attachments;
		uint32_t m_Size;
	};

	struct FrameBufferSpecification {
		uint32_t Width, Height;
		FrameBufferFormat Format;
		uint32_t Samples = 1;
	};

	class ORIGIN_API FrameBuffer {
	public:
		virtual ~FrameBuffer() = default;

		static Reference<FrameBuffer> Create(const FrameBufferSpecification& spec);
		virtual const FrameBufferSpecification& GetSpecification() const = 0;
		virtual std::vector<Attachment>& GetAttachments() = 0;

		virtual void Resize(uint32_t width, uint32_t height) = 0;


		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
	};
}