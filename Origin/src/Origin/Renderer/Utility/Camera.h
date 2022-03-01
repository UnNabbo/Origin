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
	public:
		Camera(CameraTypes type);
		~Camera();

		const glm::vec3& GetPosition() { return m_Position; }
		void SetPosition(glm::vec3 position) { m_Position = position; CalculateViewMatrix(); }

		const glm::vec3& GetRotation() { return m_Rotation; }
		void SetRotation(glm::vec3 rotation) { m_Rotation = rotation; CalculateViewMatrix(); }
	
		const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
		const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
		const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }
	private:
		void CalculateViewMatrix();

	private:
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjectionMatrix;

		glm::vec3 m_Position{ 0,0,3 };
		glm::vec3 m_Rotation{ 0,0,1 };

		CameraTypes m_Type;
	};
}
