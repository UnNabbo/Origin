#include "OGpch.h"
#include "Origin/Input/Input.h"

#include "Origin/Core/Application.h"

#include "GLFW/glfw3.h"

#include "imgui.h"

namespace Origin {
	bool Input::IsKeyPressed(int keycode) {
		ImGuiContext* context = ImGui::GetCurrentContext();
		if (0) {
			return ImGui::IsKeyDown(keycode);
			
		} else {
			const auto& Window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());

			return glfwGetKey(Window, keycode) != GLFW_RELEASE;
		}
	}

	bool Input::IsMouseButtonPressed(int button) {
		ImGuiContext* context = ImGui::GetCurrentContext();

		if (0) {
			return ImGui::IsMouseDown(button);

		} else {
			const auto& Window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());

			return glfwGetMouseButton(Window, button) != GLFW_RELEASE;
		}
	}
	std::pair<float, float> Input::GetMousePos() {
		ImGuiContext* context = ImGui::GetCurrentContext();
		if (0) {
			ImVec2 pos = ImGui::GetMousePos();
			return  { (float)pos.x, (float)pos.y };

		} else {
			const auto& Window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
			double xpos, ypos;
			glfwGetCursorPos(Window, &xpos, &ypos);

			return  { (float)xpos, (float)ypos };
		}
	} 

	void Input::LockCursor(bool state) {
		const auto& Window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		if(state)
			glfwSetInputMode(Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		else
			glfwSetInputMode(Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	}

}