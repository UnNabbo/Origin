#include "OGpch.h"
#include "Application.h"

#include "GLFW\glfw3.h"

namespace Origin {

	Application::Application(){
		m_Window = std::unique_ptr<Window>(Window::Create());
	}

	Application::~Application() {

	}

	void Application::OnStart() {}

	void Application::OnUpdate() {}

	void Application::Run() {
		OnStart();
		while (m_Running) {
			OnUpdate();
			glClearColor(1,0,1,1);
			glClear(GL_COLOR_BUFFER_BIT);
			m_Window->onUpdate();
		}
	}
}