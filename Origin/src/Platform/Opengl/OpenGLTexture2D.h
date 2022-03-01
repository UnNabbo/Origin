#pragma once

#include "Origin/Renderer/Primitives/Texture.h"

namespace Origin {
	class ORIGIN_API OpenGLTexture2D : public Texture2D {
	public:
		OpenGLTexture2D(const std::string& path);
		virtual ~OpenGLTexture2D();

		virtual uint32_t GetWidth() const override { return m_width; }
		virtual uint32_t GetHeight() const override { return m_height; };

		virtual void Bind(uint32_t slot = 0) const override;
	private:
		std::string m_path;
		uint32_t m_width, m_height;
		uint32_t m_RedererID;
	};
}