#include "OGpch.h"

#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

#include "GLFW/glfw3.h"

namespace Origin {

	Camera::Camera(CameraTypes type)
		:m_Type(type), m_ViewMatrix(1.0f) {
		switch (m_Type) {
			case Origin::CameraTypes::Orthographic: {
				m_ProjectionMatrix = glm::ortho(-1.f, 1.0f, -1.0f, 1.0f, -100.0f, 100.0f);
				break;
			}
			case Origin::CameraTypes::Projection: {
				m_ProjectionMatrix = glm::perspective(glm::radians(45.0f), 1280.0f/720.0f, 0.1f, 100.0f);
				break;
			}
			default: {
				ORIGIN_ASSERT(false, "CameraType is not a supported!");
				return;
			}
		}
		
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}


	Camera::~Camera(){
		
	}

	void Camera::CalculateViewMatrix() {

		glm::vec3 radiants_Rotation{ glm::radians(m_Rotation.x),glm::radians(m_Rotation.y), glm::radians(m_Rotation.z) };
		float theta = glm::radians(90.0f);
		glm::quat Rotation = cos(theta) + radiants_Rotation * sin(theta);

		glm::mat4 trasform = glm::translate(glm::mat4(1), m_Position) * glm::toMat4(Rotation * glm::quat(radiants_Rotation) * Rotation);

		m_ViewMatrix = glm::inverse(trasform);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;

	}
}