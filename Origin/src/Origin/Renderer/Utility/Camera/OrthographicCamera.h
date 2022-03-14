#pragma once

#include "Origin/Core/Core.h"

#include "Camera.h"

namespace Origin {
	class OrthographicCamera : public Camera {
	public:
		OrthographicCamera(float left, float right, float botton, float top);
		~OrthographicCamera() = default;

		void SetProjection(float left, float right, float bottom, float top);

		const glm::vec3& GetPosition() { return m_Position; }
		void SetPosition(glm::vec3 position) { m_Position = position; UpdateView(); }

		const glm::vec3& GetRotation() { return m_Rotation; }
		void SetRotation(glm::vec3 rotation) { m_Rotation = rotation; UpdateView(); }
	private:
		void UpdateView();
	public:
		glm::vec3 m_Position{ 0.0f, 0.0f, 0.0f };
		glm::vec3 m_Rotation{ 0.0f, 0.0f, 0.0f };

	private:
		float left = -1.28, right = 1.28, botton = -0.72, top = 0.72;

	};
}