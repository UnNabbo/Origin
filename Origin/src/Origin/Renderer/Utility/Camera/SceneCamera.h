#pragma once

#include "Origin/Core/Core.h"
#include "Camera.h"
#include "glm/glm.hpp"

namespace Origin {
	enum class ProjectionType {
		Orthographic = 0, Perspective = 1,
	};


	class ORIGIN_API SceneCamera : public Camera {
	public:
		SceneCamera() = default;
		SceneCamera(float x, float y);
		
		inline void SetViewportSize(const glm::vec2& viewport) { m_Viewport = viewport; m_AspectRatio = viewport.x / viewport.y; RecalculateProjection(); }
		inline void SetClippingPlane(const glm::vec2& clippingPlane) { m_ClippingPlane = clippingPlane; RecalculateProjection(); }
		inline void SetFov(const float& fov) { m_Fov = fov; RecalculateProjection(); }
		inline void SetSize(const float& size) { m_Size = size; RecalculateProjection(); }
		inline void SetProjectionType(ProjectionType type) { m_Type = type; RecalculateProjection(); }

		inline ProjectionType& GetProjectionType() { return m_Type; }
		inline float& GetFov() { return m_Fov; }
		inline float& GetSize() { return m_Size; }
		inline glm::vec2& GetViewPort() { return m_Viewport; }

		inline glm::vec2& GetClippingPlane() { return m_ClippingPlane; }

		inline virtual const glm::mat4& GetProjectionMatrix() const { return m_Projection; }

	private:
		void RecalculateProjection();
	private:
		glm::vec2 m_Viewport;
		float m_AspectRatio;

		glm::vec2 m_ClippingPlane{0.1f, 1000.0f};

		float m_Fov{90};
		float m_Size{10};

		glm::mat4 m_Projection = glm::mat4(1);

		ProjectionType m_Type = ProjectionType::Perspective;
	};
}