#pragma once

#include "Origin.h"

class Bird {
public:
	Bird(Origin::Reference<Origin::Texture2D>& texture);

	void Update();

	void HasCollided();

	const glm::vec3& GetPosition() {
		return m_BirdObject.position;
	}

	const glm::vec3& GetRotation() {
		return m_BirdObject.rotation;
	}

	const glm::vec2& GetSize() {
		return m_BirdObject.size;
	}

	Origin::Reference<Origin::Texture2D>& GetTexture() {
		return m_BirdObject.texture;
	}
private:
	struct Quad {
		glm::vec3 position{ 0.0f, 0.0f, 1.0f };
		glm::vec3 velocity{ 0.0f, 1.0f, 0.0f };


		glm::vec3 rotation{ 0.0f, 0.0f, 0.0f };
		glm::vec2 size{ 1.0f, 1.0f };
		Origin::Reference<Origin::Texture2D> texture;
	};

	Quad m_BirdObject;
};