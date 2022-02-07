#include "OGpch.h"

#include "WindowsWindow.h"

#include "Origin/Utility/Log/Log.h"
#include "Origin/Events/InputEvents.h"
#include "Origin/Events/ApplicationEvents.h"

#include "GLFW\glfw3.h"

#include "glad\glad.h"


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
		glfwMakeContextCurrent(m_Window);
		int GL_status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		ORIGIN_ASSERT(GL_status, "Failed to initialize Glad!");
		glfwSetWindowUserPointer(m_Window, &m_data);
		setVsync(true);

		

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int keycode, int scancode, int action, int mods){
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			switch (action) {
			case GLFW_PRESS:
				{
					KeyPressedEvent event(keycode, mods, 0);
					data.EventCallback(event);
					break;
				}
			case GLFW_REPEAT:
				{
					KeyPressedEvent event(keycode, mods, 1);
					data.EventCallback(event);
					break;
				}
			case GLFW_RELEASE:
				{
					KeyReleasedEvent event(keycode);
					data.EventCallback(event);
					break;
				}
			}

		});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xpos, double ypos) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			MouseMovedEvent event(xpos, ypos);
			data.EventCallback(event);
		});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action) {
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(button, 0);
					data.EventCallback(event);
					break;
				}
				case GLFW_REPEAT:
				{
					MouseButtonPressedEvent event(button,1);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(button);
					data.EventCallback(event);
					break;
				}
			}
		});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xoffset, double yoffset) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			MouseScrolledEvent event(xoffset, yoffset);
			data.EventCallback(event);
		});

		
		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			WindowCloseEvent event;

			data.EventCallback(event);
		});


		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			WindowResizeEvent event(width, height);
			data.Height = height;
			data.Width = width;
			data.EventCallback(event);
			glViewport(0, 0, width, height);
		});


		glfwSetWindowPosCallback(m_Window, [](GLFWwindow* window, int xpos, int ypos) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			WindowMovedEvent event(xpos, ypos);
			data.EventCallback(event);
		});


		glfwSetWindowFocusCallback(m_Window, [](GLFWwindow* window, int focused) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			if (focused) {
				WindowFocusEvent event;
				data.EventCallback(event);
			}
			else {
				WindowLostFocusEvent event;
				data.EventCallback(event);
			}

		});

		glfwSetCharCallback(m_Window, [](GLFWwindow* window, uint32_t character) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			KeyTypedEvent event(character);
			data.EventCallback(event);
		});
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