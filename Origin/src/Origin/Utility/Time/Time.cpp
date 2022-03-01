#include "OGpch.h"
#include "Time.h"

#include "GLFW/glfw3.h"

namespace Origin{
	void Time::Update() {
		float newTime = (float)glfwGetTime();
		m_DeltaTime = newTime - m_CurrentTime;
		m_CurrentTime = newTime;
	}
}