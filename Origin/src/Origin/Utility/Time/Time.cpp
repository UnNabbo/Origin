#include "OGpch.h"
#include "Time.h"

#include "GLFW/glfw3.h"

namespace Origin{
	void Time::Update() {
		m_TimeFromStart = (float)glfwGetTime();
		m_DeltaTime = m_TimeFromStart - m_CurrentTime;
		m_CurrentTime = m_TimeFromStart;
	}

	float Time::GetTime() {
		return m_TimeFromStart;
	}
}