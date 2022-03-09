#include "OGpch.h"

#include "Origin/Utility/Log/Log.h"

#include "OpenGLContex.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace Origin {
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle) 
		: m_windowHandle(windowHandle) {
		ORIGIN_ASSERT(windowHandle, "Window pointer is not valid!");
	}

	void OpenGLContext::Init() {
		glfwMakeContextCurrent(m_windowHandle);
		int GL_status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		ORIGIN_ASSERT(GL_status, "Failed to initialize Glad!");
		ORIGIN_INFO("OpenGL Infos:\nVendor: {0}\nRenderer: {1}\nVersion: {2}", glGetString(GL_VENDOR), glGetString(GL_RENDERER), glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers() {
		glfwSwapBuffers(m_windowHandle);
	}
}