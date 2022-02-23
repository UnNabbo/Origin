#pragma once

#include "Core.h"

#include "Layer/LayerStack.h"
#include "Events/ApplicationEvents.h"

#include "Origin/Window.h"
#include "Origin/Input/Input.h"

#include "Origin/Utility/Imgui/ImGuiLayer.h"

#include "Renderer/Buffers.h"

#include "Renderer/VertexArray.h"

#include "Origin/Renderer/Shader.h"


namespace Origin {
	class ORIGIN_API Application {
	public:
		Application();

		virtual ~Application();

		void OnEvents(Event& e);


		inline void PushLayer(Layer* layer) { m_LayerStack.PushLayer(layer);  }
		inline void PushOverlay(Layer* overlay) { m_LayerStack.PushOverlay(overlay); }
		inline void PopLayer(Layer* layer) { m_LayerStack.PopLayer(layer); }
		inline void PopOverlay(Layer* overlay) { m_LayerStack.PopOverlay(overlay); }

		inline Window& GetWindow() { return *m_Window; }
		inline static Application& Get() { return *s_Instace; }

		void Run();
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		LayerStack m_LayerStack;
		std::unique_ptr<Window> m_Window;

		ImGuiLayer* m_ImGuiLayer;

		bool m_Running = true;

		inline static Application* s_Instace = nullptr;

		std::shared_ptr<VertexArray> VAO;
		std::shared_ptr<VertexBuffer> VBO;
		std::shared_ptr<IndexBuffer> IBO;
		std::shared_ptr<Shader> shader;

		

		std::shared_ptr<VertexArray> square_VAO;

	};
}

