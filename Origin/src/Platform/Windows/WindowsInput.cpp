#include "OGpch.h"
#include "WindowsInput.h"

#include "Origin/Application.h"

#include "GLFW/glfw3.h"

namespace Origin {
	Input* Input::m_Instace = new WindowsInput;

	bool WindowsInput::IsKeyPressedImpl(int keycode) {
		const auto& Window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());

		return glfwGetKey(Window, keycode) != GLFW_RELEASE;
	}
	bool WindowsInput::IsMouseButtonPressedImpl(int button) {
		const auto& Window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());

		return glfwGetMouseButton(Window, button) != GLFW_RELEASE;
	}
	std::pair<float, float> WindowsInput::GetMousePosImpl() {
		const auto& Window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double xpos, ypos;
		glfwGetCursorPos(Window, &xpos, &ypos);

		return  { (float)xpos, (float)ypos };
	} 
}