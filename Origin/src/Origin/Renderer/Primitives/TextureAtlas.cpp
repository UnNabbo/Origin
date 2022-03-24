#include "OGpch.h"

#include "TextureAtlas.h"

namespace Origin {
	Reference<TextureAtlas> TextureAtlas::Create(const std::string& path, const glm::vec2& spriteSize) {
		Reference<Texture2D> texture = Texture2D::Create(path);

		return MakeReference<TextureAtlas>(texture, spriteSize);
	}

	TextureAtlas::TextureAtlas(Reference<Texture2D>& texture, const glm::vec2& spriteSize) 
		: m_BaseTexture(texture) ,m_spriteSize(spriteSize){
		m_BaseSize = { m_BaseTexture->GetWidth(), m_BaseTexture->GetHeight() };
	}

	Reference<SubTexture2D> TextureAtlas::GetSubTexture(const glm::vec2& postion, const glm::vec2& size) {

		glm::vec2 begin;
		begin.x = (postion.x * m_spriteSize.x) / m_BaseSize.x;
		begin.y = (postion.y * m_spriteSize.y) / m_BaseSize.y;

		glm::vec2 end;
		end.x = ((postion.x + size.x) * m_spriteSize.x) / m_BaseSize.x;
		end.y = ((postion.y + size.y) * m_spriteSize.y) / m_BaseSize.y;


		ORIGIN_TRACE("({0}, {2}), ({1}, {3})", (postion.x * m_spriteSize.x), (postion.y * m_spriteSize.y), ((postion.x + size.x) * m_spriteSize.x), ((postion.y + size.y) * m_spriteSize.y));

		return MakeReference<SubTexture2D>(m_BaseTexture, begin, end);
	}
}