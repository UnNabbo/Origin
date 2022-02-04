#include "OGpch.h"

#include "Application.h"

#include "util\log\Log.h"


namespace Origin {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application::Application(){
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->setEventCallback(BIND_EVENT_FN(OnEvents));
	}

	Application::~Application() {

	}

	void Application::OnStart() {}

	void Application::OnUpdate() {}

	bool Application::OnKeyPress(KeyPressedEvent& e) {
		ORIGIN_INFO("DIO");
		return true;
	}

	bool Application::OnMouseMove(MouseMovedEvent& e) {
		ORIGIN_INFO("Moved");
		return true;
	}

	bool Application::OnWindowClose(WindowCloseEvent& e) {
		m_Running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e) {
		ORIGIN_INFO("Width: {0}  Height {1}", m_Window->getWidth(), m_Window->getHeight());
		return true;
	}

	void Application::OnEvents(Event& e) {
		EventsDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(OnWindowResize));

	}


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