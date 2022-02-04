#include "OGpch.h"
#include "WindowsWindow.h"

#include "Origin\util\log\Log.h"

namespace Origin {

	inline static bool GLFW_init = false;

	Window* Window::Create(const WindowStruct& info) {
		return new WindowsWindow(info);
	}

	WindowsWindow::WindowsWindow(const WindowStruct& info) {
		Init(info);
	}

	WindowsWindow::~WindowsWindow(){
		Shutdown();
	}

	void WindowsWindow::Init(const WindowStruct& info) {
		m_data.Title = info.Title;
		m_data.Width = info.Width;
		m_data.Height = info.Height;

		ORIGIN_INFO("Creating Windows {0} ({1}, {2})", m_data.Title, m_data.Width, m_data.Height);


		if (!GLFW_init) {
			int state = glfwInit();

			ORIGIN_ASSERT(state, "Could not initialize GLFW!");

			GLFW_init = true;
		}

		m_Window = glfwCreateWindow(m_data.Width, m_data.Height, m_data.Title, nullptr, nullptr);
		glfwSetWindowUserPointer(m_Window, &m_data);
		glfwMakeContextCurrent(m_Window);
		setVsync(true);
	}

	void WindowsWindow::Shutdown() {
		glfwDestroyWindow(m_Window);
	}

	void WindowsWindow::onUpdate() {
		glfwPollEvents();

		glfwSwapBuffers(m_Window);
	}

	void WindowsWindow::setVsync(bool state) {
		m_data.Vsync = state;

		glfwSwapInterval(state);
	}

}