 #include "OGpch.h"

#include "Application.h"

#include "Origin/Utility/Log/Log.h"

#include "Origin/Utility/Time/Time.h"

#include "Origin/Renderer/Renderer.h"

#include "ResourceManager/AssetPool.h"

#include "imgui.h"

namespace Origin {

	Application::Application(){
		ORIGIN_ASSERT(!s_Instace, "Application is a Sigleton, only one instace may be created.")
		s_Instace = this;
		m_Window = ScopedReference<Window>(Window::Create());
		m_Window->setEventCallback(BIND_EVENT_FN(Application::OnEvents));
		m_Window->setVsync(false);

		Renderer::Init();

		m_ImGuiLayer = new ImGuiLayer;
		PushOverlay(m_ImGuiLayer);

	}

	Application::~Application() {
		//Pool::Clear();
		ShaderAssetPool::Clear();
		VertexArrayAssetPool::Clear();
	}

	bool Application::OnWindowClose(WindowCloseEvent& e) {
		m_Running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e) {
		if (e.GetWidth() == 0 || e.GetHeight() == 0) {
			return false;
		}
		Renderer::ResizeWindow(e.GetWidth(), e.GetHeight());
		return false;
	}

	void Application::OnEvents(Event& e) {
		EventsDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(Application::OnWindowResize));

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

			Time::Update();
		}

	}
}