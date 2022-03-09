#pragma once

#include "Origin/Core/Core.h"

#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"
#include "glm/gtx/quaternion.hpp"


namespace Origin {

	enum class CameraTypes {
		None = 0,
		Orthographic, Projection,
	};


	class ORIGIN_API Camera {
	protected:
		Camera() = default;
		Camera(const glm::mat4 projection) : m_Projection(projection) {}
	public:
		virtual ~Camera() = default;

		const glm::mat4& GetProjectionMatrix() const { return m_Projection; }
		const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
		const glm::mat4& GetViewProjection() const { return m_Projection * m_ViewMatrix; }

	protected:
		glm::mat4 m_Projection = glm::mat4(1);
		glm::mat4 m_ViewMatrix = glm::mat4(1);

	};
}
