#include "OGpch.h"

#include "Application.h"

#include "Origin/Utility/Log/Log.h"

#include "Origin/Utility/FileSystem/FileStream.h"

#include "Origin/Utility/ResourceManager/AssetPool.h"



#include <glad/glad.h>


namespace Origin {

	Application::Application(){
		ORIGIN_ASSERT(!s_Instace, "Application is a Sigleton, only one instace may be created.")
		s_Instace = this;
		m_Window = std::unique_ptr<Window>(Window::Create());

		m_Window->setEventCallback(BIND_EVENT_FN(Application::OnEvents));
		
		m_ImGuiLayer = new ImGuiLayer;
		PushOverlay(m_ImGuiLayer);

		shader.reset(Shader::Create("E:/DEV/Origin/Origin/asset/Vertex.shader", "E:/DEV/Origin/Origin/asset/Fragment.shader"));

		VAO.reset(VertexArray::Create());
		VBO.reset(VertexBuffer::Create());
		IBO.reset(IndexBuffer::Create());


		VAO->Bind();
		VBO->Bind();
		IBO->Bind();

		
		shader->Bind();
		
		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
		};

		float square_vertices[4 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
			 0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
			-0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
		};

		uint32_t indices[] = {
			0,1,2,
		};

		uint32_t  square_indices[] = {
			0,1,2,2,3,0
		};

		VBO->SetData(vertices, sizeof(vertices));
		IBO->SetData(indices, sizeof(indices));


		BufferLayout layout = {
			{ShaderDataType::Float3, "a_Position"},
			{ShaderDataType::Float4, "a_Color"},

		};

		VBO->SetLayout(layout);

		VAO->AddVertexBuffer(VBO);
		VAO->SetIndexBuffer(IBO);

		square_VAO.reset(VertexArray::Create());

		std::shared_ptr<VertexBuffer> square_VBO;
		square_VBO.reset(VertexBuffer::Create(square_vertices, sizeof(square_vertices)));
		square_VBO->Bind();
		square_VBO->SetLayout(layout);
		std::shared_ptr<IndexBuffer> square_IBO;
		square_IBO.reset(IndexBuffer::Create(square_indices, sizeof(square_indices)));
		square_IBO->Bind();
		square_VAO->AddVertexBuffer(square_VBO);
		square_VAO->SetIndexBuffer(square_IBO);
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

			glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			square_VAO->Bind();
			shader->Bind();
			glDrawElements(GL_TRIANGLES, square_VAO->GetIndexBuffers()->GetCount(), GL_UNSIGNED_INT, 0);


			VAO->Bind();
			shader->Bind();
			glDrawElements(GL_TRIANGLES, VAO->GetIndexBuffers()->GetCount(), GL_UNSIGNED_INT, 0);
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