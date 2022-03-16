#pragma once

#include "Origin/Renderer/Primitives/Texture.h"

#include <glad/glad.h>

#include "Origin/Utility/FileSystem/Files.h"

namespace Origin {
	class ORIGIN_API OpenGLTexture2D : public Texture2D {
	public:
		OpenGLTexture2D(uint32_t width, uint32_t height);

		OpenGLTexture2D(const std::string& path);
		virtual ~OpenGLTexture2D();

		virtual uint32_t GetWidth() const override { return m_width; }
		virtual uint32_t GetHeight() const override { return m_height; };
		virtual std::string GetName() const override { return File::GetName(m_path.c_str()); };

		virtual void SetData(void* data, size_t size) override;

		virtual void Bind(uint32_t slot = 0) const override;
	private:
		std::string m_path;
		uint32_t m_width, m_height;
		uint32_t m_RedererID;
		GLenum m_InternalFormat, m_Format;
	};
}