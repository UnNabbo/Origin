#pragma once

#include "Origin/Core/Core.h"
#include "glm/glm.hpp"

namespace Origin {
	class ORIGIN_API Texture {
	public:
		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;
		virtual std::string GetName() const = 0;
		virtual void SetData(void* data, size_t size) = 0;

		virtual void Bind(uint32_t slot) const = 0;
	};

	class ORIGIN_API Texture2D : public Texture {
	public:
		virtual ~Texture2D() = default;

		static Reference<Texture2D> Create(uint32_t width, uint32_t height);
		static Reference<Texture2D> Create(const std::string& path);
		virtual bool operator== (const Texture2D& other) const = 0;
	};

	class ORIGIN_API SubTexture2D{
	public:
		SubTexture2D(Reference<Texture2D> texture, glm::vec2& begin, glm::vec2& max);
		Reference<Texture2D>& GetTexture();

		const glm::vec2& GetBegin();
		const glm::vec2& GetEnd();

		
	private:
		Reference<Texture2D> m_BaseTexture;
		glm::vec2 m_Begin, m_End;
	};
	
}