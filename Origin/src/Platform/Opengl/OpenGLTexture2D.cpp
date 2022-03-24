#include "OGpch.h"

#include "OpenGLTexture2D.h"

#include <stb_image.h>

namespace Origin {
	OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height)
		: m_width(width), m_height(height), m_path("Null") {

		m_InternalFormat = GL_RGBA8;
		m_Format = GL_RGBA;

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RedererID);
		glTextureStorage2D(m_RedererID, 1, m_InternalFormat, m_width, m_height);

		glTextureParameteri(m_RedererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RedererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	}
	
	OpenGLTexture2D::OpenGLTexture2D(const std::string& path)
		: m_path(path) {
		int width, height, channels;
		stbi_set_flip_vertically_on_load(1);
		stbi_uc * data = stbi_load(path.c_str(), &width, &height, &channels, 0);
		ORIGIN_ASSERT(data, "Failed To load {} as an image!", m_path);
		m_width = width;
		m_height = height;

		switch (channels) {
			case 4: {
				m_InternalFormat = GL_RGBA8;
				m_Format = GL_RGBA;
				break;
			}
			case 3: {
				m_InternalFormat = GL_RGB8;
				m_Format = GL_RGB;
				break;
			}
		}

		ORIGIN_ASSERT(m_InternalFormat & m_Format, "Fornat not supported!");

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RedererID);
		glTextureStorage2D(m_RedererID, 1, m_InternalFormat, m_width, m_height);

		glTextureParameteri(m_RedererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RedererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureSubImage2D(m_RedererID, 0, 0, 0, m_width, m_height, m_Format, GL_UNSIGNED_BYTE, data);

		stbi_image_free(data);
	}

	OpenGLTexture2D::~OpenGLTexture2D() {
		glDeleteTextures(1, &m_RedererID);
	}

	void OpenGLTexture2D::SetData(void* data, size_t size) {
		glTextureSubImage2D(m_RedererID, 0, 0, 0, m_width, m_height, m_Format, GL_UNSIGNED_BYTE, data);
	}

	void OpenGLTexture2D::Bind(uint32_t slot) const {
		glBindTextureUnit(slot, m_RedererID);
	}
}
