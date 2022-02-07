#include "OGpch.h"

#include "Application.h"

#include "Origin/Utility/Log/Log.h"


#include "glad/glad.h"



namespace Origin {


	Application::Application(){
		ORIGIN_ASSERT(!s_Instace, "Application is a Sigleton, only one instace may be created.")
		s_Instace = this;
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->setEventCallback(BIND_EVENT_FN(Application::OnEvents));
	}

	Application::~Application() {

	}

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
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));

		for (auto layer = m_LayerStack.end(); layer != m_LayerStack.begin();) {
			(*--layer)->OnEvent(e);
			if (e.handled) {
				break;
			}
		}
	}



	void Application::Run() {
		while (m_Running) {
			glClearColor(1,0,1,1);
			glClear(GL_COLOR_BUFFER_BIT);

			for (Layer* layer : m_LayerStack) {
				layer->OnUpdate();
			}

			auto [x, y] = Input::GetMousePos();
			ORIGIN_TRACE("{0}, {1}", x, y);

			m_Window->onUpdate();
		}
	}
}