#include "OGpch.h"

#include "Application.h"

#include "Origin/Utility/Log/Log.h"

#include "glad/glad.h"

#include "Origin/Utility/ResourceManager/ResourceManager.h"

namespace Origin {
	Application::Application(){
		ORIGIN_ASSERT(!s_Instace, "Application is a Sigleton, only one instace may be created.")
		s_Instace = this;
		m_Window = std::unique_ptr<Window>(Window::Create());

		m_Window->setEventCallback(BIND_EVENT_FN(Application::OnEvents));
		
		m_ImGuiLayer = new ImGuiLayer;
		PushOverlay(m_ImGuiLayer);

		glGenVertexArrays(1, &m_VAO);
		VBO = VertexBuffer::Create();
		EBO = IndexBuffer::Create();


		glBindVertexArray(m_VAO);
		VBO->Bind();
		EBO->Bind();

		float vertices[4 * 3] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f,

		};

		uint32_t indices[] = {
			0,1,2,
			2,3,0
		};

		VBO->SetData(vertices, sizeof(vertices));
		EBO->SetData(indices, sizeof(indices));

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, false, 3 * sizeof(float), nullptr);

		ResourceManager::Load("Dio");
		ORIGIN_TRACE("{0}", (char*)ResourceManager::Retrive("Dio"));
		ResourceManager::Load("Dio");
		ResourceManager::Unload("Dio");
		ResourceManager::Unload("Dio");
		ORIGIN_TRACE("{0}", (char*)ResourceManager::Retrive("Dio"));

	}

	Application::~Application() {

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

			glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
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