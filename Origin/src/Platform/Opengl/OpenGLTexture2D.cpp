#include "OGpch.h"

#include "OpenGLTexture2D.h"

#include <stb_image.h>

#include <glad/glad.h>

namespace Origin {
	OpenGLTexture2D::OpenGLTexture2D(const std::string& path)
		: m_path(path) {
		int width, height, channels;
		stbi_set_flip_vertically_on_load(1);
		stbi_uc * data = stbi_load(path.c_str(), &width, &height, &channels, 0);
		ORIGIN_ASSERT(data, "Failed To load {} as an image!", m_path);
		m_width = width;
		m_height = height;

		GLenum internalFormat = 0;
		GLenum dataFormat = 0;

		switch (channels) {
			case 4: {
				internalFormat = GL_RGBA8;
				dataFormat = GL_RGBA;
				break;
			}
			case 3: {
				internalFormat = GL_RGB8;
				dataFormat = GL_RGB;
				break;
			}
		}

		ORIGIN_ASSERT(internalFormat & dataFormat, "Fornat not supported!");

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RedererID);
		glTextureStorage2D(m_RedererID, 1, internalFormat, m_width, m_height);

		glTextureParameteri(m_RedererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RedererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureSubImage2D(m_RedererID, 0, 0, 0, m_width, m_height, dataFormat, GL_UNSIGNED_BYTE, data);

		stbi_image_free(data);
	}

	OpenGLTexture2D::~OpenGLTexture2D() {
		glDeleteTextures(1, &m_RedererID);
	}

	void OpenGLTexture2D::Bind(uint32_t slot) const {
		glBindTextureUnit(slot, m_RedererID);
	}
}
