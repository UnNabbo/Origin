#include "OGpch.h"

#include "ProjectionCamera.h"

namespace Origin {
	ProjectionCamera::ProjectionCamera(float fov, float aspectRatio, float nearClip, float farClip)
		: Camera(glm::perspective(glm::radians(fov), aspectRatio, nearClip, farClip)), m_FOV(fov), m_AspectRatio(aspectRatio), m_NearClip(nearClip), m_FarClip(farClip){
		UpdateView();
	}

	void ProjectionCamera::SetProjection(float fov, float aspectRatio, float nearClip, float farClip) {
		m_Projection = glm::perspective(glm::radians(fov), aspectRatio, nearClip, farClip);
	}

	void ProjectionCamera::UpdateProjection() {
		m_AspectRatio = m_ViewportWidth / m_ViewportHeight;
		m_Projection = glm::perspective(glm::radians(m_FOV), m_AspectRatio, m_NearClip, m_FarClip);
	}

	void ProjectionCamera::UpdateView() {

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


		m_ViewMatrix =  glm::translate(glm::mat4(1), m_Position) * glm::toMat4(orientation);

		m_ViewMatrix = glm::inverse(m_ViewMatrix);

	}



}