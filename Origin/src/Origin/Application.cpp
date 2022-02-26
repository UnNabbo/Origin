#include "OGpch.h"

#include "Application.h"

#include "Utility/Log/Log.h"

#include "Utility/ResourceManager/AssetPool.h"


namespace Origin {

	Application::Application(){
		ORIGIN_ASSERT(!s_Instace, "Application is a Sigleton, only one instace may be created.")
		s_Instace = this;
		m_Window = std::unique_ptr<Window>(Window::Create());

		m_Window->setEventCallback(BIND_EVENT_FN(Application::OnEvents));
		
		m_ImGuiLayer = new ImGuiLayer;
		PushOverlay(m_ImGuiLayer);

	}

	Application::~Application() {
		AssetPool::Clear();
	}

	bool Application::OnWindowClose(WindowCloseEvent& e) {
		m_Running = false;
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

			for (Layer* layer : m_LayerStack) {
				layer->OnUpdate();
			}

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack) {
				layer->OnImGuiRender();
			}
			m_ImGuiLayer->End();

			m_Window->onUpdate();

		}

	}
}