#include "OGpch.h"
#include "EditorCamera.h"

#include "Origin/Input/Input.h"
#include "Origin/Input/MouseCodes.h"
#include "Origin/Input/KeyCodes.h"
#include <math.h>    

#include "Origin/Utility/Time/Time.h"

namespace Origin {
	EditorCamera::EditorCamera(float fov, float aspectRatio, float nearClip, float farClip)
		: Camera(glm::perspective(glm::radians(fov), aspectRatio, nearClip, farClip)), m_FOV(fov), m_AspectRatio(aspectRatio), m_NearClip(nearClip), m_FarClip(farClip) {
		UpdateView();
	}

	void EditorCamera::SetProjection(float fov, float aspectRatio, float nearClip, float farClip) {
		m_Projection = glm::perspective(glm::radians(fov), aspectRatio, nearClip, farClip);
	}

	void EditorCamera::UpdateProjection() {
		if (m_ViewportWidth == 0 || m_ViewportHeight == 0) {
			return;
		}
		m_AspectRatio = m_ViewportWidth / m_ViewportHeight;
		m_Projection = glm::perspective(glm::radians(m_FOV), m_AspectRatio, m_NearClip, m_FarClip);
	}

	void EditorCamera::UpdateView() {


		glm::quat orientation = GetOrientation();

		m_ViewMatrix = glm::translate(glm::mat4(1), m_Position) * glm::toMat4(orientation);

		m_ViewMatrix = glm::inverse(m_ViewMatrix);

	}

	void EditorCamera::OnUpdate() {
		if (Input::IsMouseButtonPressed(OG_MOUSE_BUTTON_MIDDLE)) {
			Input::LockCursor(true);
			glm::vec2 delta = GetMouseDelta();


			auto [xSpeed, ySpeed] = PanSpeed();
			m_Position += -GetRightDirection() * delta.x * xSpeed * m_Distance;
			m_Position += GetUpDirection() * delta.y * ySpeed * m_Distance;

		} else if (Input::IsMouseButtonPressed(OG_MOUSE_BUTTON_RIGHT)) {
			Input::LockCursor(true);

			glm::vec2 delta = GetMouseDelta();

			if (!m_RotationLock) {
				float yawSign = GetUpDirection().y < 0 ? 1.0f : -1.0f;
				m_Rotation.y += yawSign * delta.x * 0.8f;
				m_Rotation.x += -delta.y * 0.8f;
			} else {
				auto [xSpeed, ySpeed] = PanSpeed();
				m_Position += -GetRightDirection() * delta.x * xSpeed * m_Distance;
				m_Position += GetUpDirection() * delta.y * ySpeed * m_Distance;
			}
		}
		if (!Input::IsMouseButtonPressed(OG_MOUSE_BUTTON_MIDDLE) && !Input::IsMouseButtonPressed(OG_MOUSE_BUTTON_RIGHT)) {
			auto [x, y] = Input::GetMousePos();
			const glm::vec2& mouse{ x, y };
			Input::LockCursor(false);
			m_InitialMousePosition = mouse;
		}
		UpdateView();
	}

	std::pair<float, float> EditorCamera::PanSpeed() const {
		float x = std::min(m_ViewportWidth / 1000.0f, 2.4f); // max = 2.4f
		float xFactor = 0.0366f * (x * x) - 0.1778f * x + 0.3021f;

		float y = std::min(m_ViewportHeight / 1000.0f, 2.4f); // max = 2.4f
		float yFactor = 0.0366f * (y * y) - 0.1778f * y + 0.3021f;

		return { xFactor, yFactor };
	}

	glm::vec2 EditorCamera::GetMouseDelta() {
		auto [x, y] = Input::GetMousePos();
		const glm::vec2& mouse{ x, y };
		glm::vec2 delta = (mouse - m_InitialMousePosition) * 0.003f;
		m_InitialMousePosition = mouse;
		return delta;
	}

	bool EditorCamera::OnMouseScrolled(MouseScrolledEvent& e) {
		float delta = e.GetYoffset();
		
		float distance = m_Distance * 0.1f;
		distance = std::max(distance, 0.0f);
		float ZoomSpeed = distance * distance;
		ZoomSpeed = std::min(ZoomSpeed, 25.0f);

		
		m_Position += GetForwardDirection() * delta * ZoomSpeed;
		m_Distance = std::sqrt(m_Position.x * m_Position.x + m_Position.y * m_Position.y + m_Position.z * m_Position.z);
		return true;
	}

	bool EditorCamera::OnWindowResize(WindowResizeEvent& e) {
		SetViewportSize(e.GetWidth(), e.GetHeight());
		return false;
	}


	void EditorCamera::OnEvent(Event& e) {
		EventsDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(BIND_EVENT_FN(EditorCamera::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(EditorCamera::OnWindowResize));

	}

	void EditorCamera::setOrthographic(bool state) {
		m_RotationLock = state;
		if (state) {
			m_Rotation = { 0,0,0 };
			UpdateView();
		}
	}

	glm::vec3 EditorCamera::GetUpDirection() const {
		return glm::rotate(GetOrientation(), glm::vec3(0.0f, 1.0f, 0.0f));
	}

	glm::vec3 EditorCamera::GetRightDirection() const {
		return glm::rotate(GetOrientation(), glm::vec3(1.0f, 0.0f, 0.0f));
	}

	glm::vec3 EditorCamera::GetForwardDirection() const {
		return glm::rotate(GetOrientation(), glm::vec3(0.0f, 0.0f, -1.0f));
	}

	glm::quat EditorCamera::GetOrientation() const {
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

		return orientation;
	}
}