#pragma once

#include "Origin.h"

#include <random>

class Pipe {
public:
	Pipe(Origin::Reference<Origin::Texture2D>& texture);
	
	void Update(uint32_t& offset);

	void DrawPipe(uint32_t offset = 0);

	const bool IsInsidePipe(const glm::vec3& pos);

	const glm::vec3& GetPosition() {
		return m_PipeObject.position;
	}

	void SetPosition(glm::vec3& position) {
		m_PipeObject.position = position;
	}


	const glm::vec3& GetRotation() {
		return m_PipeObject.rotation;
	}
	void SetRotation(glm::vec3& rotation) {
		m_PipeObject.rotation = rotation;
	}


	const glm::vec2& GetSize() {
		return m_PipeObject.size;
	}
	void SetSize(glm::vec2& size) {
		m_PipeObject.size = size;
	}


	Origin::Reference<Origin::Texture2D>& GetTexture() {
		return m_PipeObject.texture;
	}
private:
	struct Quad {
		glm::vec3 position{ 12.8f, -6.0f, 0.0f };
		glm::vec3 rotation{ 0.0f, 0.0f, 0.0f };
		glm::vec2 size{ 2.0f, 8.0f };
		Origin::Reference<Origin::Texture2D> texture;
	};

	float velocity = 16.0f;

	Quad m_PipeObject;
};