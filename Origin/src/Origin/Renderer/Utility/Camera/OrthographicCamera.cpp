#include "OGpch.h"

#include "OrthographicCamera.h"

#include <glm/gtc/matrix_transform.hpp>

#include "GLFW/glfw3.h"

namespace Origin {

	OrthographicCamera::OrthographicCamera(float left, float right, float botton, float top)
		: Camera(glm::ortho(left, right, botton, top, -100.0f, 100.0f)) {
		UpdateView();
	}

	void OrthographicCamera::SetProjection(float left, float right, float botton, float top) {
		m_Projection = glm::ortho(left, right, botton, top, -100.0f, 100.0f);
	}

	void OrthographicCamera::UpdateView() {

		glm::quat orientation;

		double cy = cos(m_Rotation.z * 0.5);
		double sy = sin(m_Rotation.z * 0.5);
		double cp = cos(m_Rotation.y * 0.5);
		double sp = sin(m_Rotation.y * 0.5);
		double cr = cos(m_Rotation.x * 0.5);
		double sr = sin(m_Rotation.x * 0.5);

		orientation.w = cr * cp * cy + sr * sp * sy;
		orientation.x = sr * cp * cy - cr * sp * sy;
		orientation.y = cr * sp * cy + sr * cp * sy;
		orientation.z = cr * cp * sy - sr * sp * cy;


		m_Position *= glm::rotate(orientation, glm::vec3(0.0f, 0.0f, -1.0f));

		m_ViewMatrix = glm::translate(glm::mat4(1), m_Position) * glm::toMat4(orientation);

		m_ViewMatrix = glm::inverse(m_ViewMatrix);

	}
}