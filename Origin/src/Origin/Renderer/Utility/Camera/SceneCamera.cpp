#include "OGpch.h"

#include "SceneCamera.h"

namespace Origin {
	SceneCamera::SceneCamera(float x, float y) : m_Viewport({x, y}), m_AspectRatio(x / y) {
		RecalculateProjection();
	}

	void SceneCamera::RecalculateProjection() {
		if (m_Viewport.x == 0 || m_Viewport.y == 0) {
			return;
		}

		if (m_Type == ProjectionType::Perspective) {
			m_Projection = glm::perspective(glm::radians(m_Fov), m_AspectRatio, m_ClippingPlane.x, m_ClippingPlane.y);
		} else {
			m_Projection = glm::ortho(-m_AspectRatio * m_Size * 0.5f, m_AspectRatio * m_Size * 0.5f, -m_Size * 0.5f, m_Size * 0.5f, m_ClippingPlane.x, m_ClippingPlane.y);
		}

	}
}