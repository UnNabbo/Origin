#include "Bird.h"

Bird::Bird(Origin::Reference<Origin::Texture2D>& texture) {
	m_BirdObject.texture = texture;
}

void Bird::Update() {
	if (Origin::Input::IsKeyPressed(OG_KEY_SPACE)) {
		m_BirdObject.velocity.y = 5;
	} else {

		m_BirdObject.velocity.y -= 0.01;
	}

	m_BirdObject.rotation.z = m_BirdObject.velocity.y * glm::radians(9.0f);
	if (m_BirdObject.rotation.z < glm::radians(-90.0f)) {
		m_BirdObject.rotation.z = glm::radians(-90.0f);
	}


	m_BirdObject.position.y += m_BirdObject.velocity.y * Origin::Time::GetSeconds();


}

void Bird::HasCollided() {
	m_BirdObject.velocity.y = 0;
}