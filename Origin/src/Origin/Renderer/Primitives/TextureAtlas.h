#pragma once

#include "Origin/Core/Core.h"

#include "Texture.h"

#include <glm/glm.hpp>

namespace Origin {
	

	class ORIGIN_API TextureAtlas{
	public:
		static Reference<TextureAtlas> Create(const std::string& path, const glm::vec2& spriteSize);

		TextureAtlas(Reference<Texture2D>& texture, const glm::vec2& spriteSize);

		Reference<SubTexture2D> GetSubTexture(const glm::vec2& postion, const glm::vec2& size);
	private:
		Reference<Texture2D> m_BaseTexture;
		glm::vec2 m_BaseSize;
		glm::vec2 m_spriteSize;
	};
}