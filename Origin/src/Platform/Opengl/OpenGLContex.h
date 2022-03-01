#pragma once

#include "Origin/Core/Core.h"

#include "Origin/Renderer/GraphicsContex.h"

#include "GLFW/glfw3.h"
#include "glad/glad.h"

struct GLFWwindow;

namespace Origin {
	class ORIGIN_API OpenGLContext : public GraphicsContext {
	public:
		OpenGLContext(GLFWwindow* windowHandle);

		virtual void Init() override;
		virtual void SwapBuffers() override;
	private:
		GLFWwindow* m_windowHandle;
	};
}