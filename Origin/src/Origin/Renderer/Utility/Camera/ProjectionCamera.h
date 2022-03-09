#pragma once

#include "Origin/Core/Core.h"

#include "Camera.h"

namespace Origin {
	class ProjectionCamera : public Camera {
	public:
		ProjectionCamera(float fov, float aspectRatio, float nearClip, float farClip);
		~ProjectionCamera() = default;

		void SetProjection(float fov, float aspectRatio, float nearClip, float farClip);
		void UpdateProjection();

		inline const glm::vec3& GetPosition() { return m_Position; }
		inline void SetPosition(glm::vec3 position) { m_Position = position; UpdateView(); }

		inline const glm::vec3& GetRotation() { return m_Rotation; }
		inline void SetRotation(glm::vec3 rotation) { m_Rotation = rotation; UpdateView(); }

		inline void SetViewportSize(float width, float height) { m_ViewportWidth = width; m_ViewportHeight = height; UpdateProjection(); }

		inline const float& GetFOV() { return m_FOV; }
		inline void setFOV(float fov) { m_FOV = fov; }

	private:
		void UpdateView();

	private:
		float m_FOV = 45.0f, m_AspectRatio = 1.0f, m_NearClip = 0.1f, m_FarClip = 1000.0f;

		glm::vec3 m_Position{ 0.0f, 0.0f, -5.0f };
		glm::vec3 m_Rotation{ 0.0f, 0.0f, 0.0f };

		float m_ViewportWidth = 1280, m_ViewportHeight = 720;
	};
}