#include "Pipe.h"

#include "../Random/Random.h"


Pipe::Pipe(Origin::Reference<Origin::Texture2D>& texture) {
	m_PipeObject.texture = texture;
}

void Pipe::DrawPipe(uint32_t offset) {
	Origin::Renderer2D::DrawRotatedQuad(glm::vec3(m_PipeObject.position.x, m_PipeObject.position.y + offset, m_PipeObject.position.z), m_PipeObject.rotation, m_PipeObject.size, m_PipeObject.texture);
}

const bool Pipe::IsInsidePipe(const glm::vec3& pos) {
	//glm::quat rotation = Origin::EulerToQuat(rot);

	if (pos.y <= m_PipeObject.position.y + m_PipeObject.size.y / 2 & pos.y>= m_PipeObject.position.y - m_PipeObject.size.y / 2) {
		if (pos.x <= m_PipeObject.position.x + m_PipeObject.size.x / 2 & pos.x >= m_PipeObject.position.x - m_PipeObject.size.x / 2) {
			return true;
		}
	}
	return false;
}

void Pipe::Update(uint32_t& offset) {
	if(m_PipeObject.position.x + m_PipeObject.size.x / 2 >= -12.8)
		m_PipeObject.position.x += -velocity * Origin::Time::GetSeconds();
	else {
		m_PipeObject.position.x = 12.8;
	}
}