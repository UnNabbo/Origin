#pragma once

#include "Core.h"

#include "LayerStack.h"
#include "Platform/Windows/WindowsWindow.h"
#include "Events/InputEvents.h"
#include "Events/ApplicationEvents.h"

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


		void Run();
	private:
		bool OnKeyPress(KeyPressedEvent& e);

		bool OnMouseMove(MouseMovedEvent& e);

		bool OnWindowClose(WindowCloseEvent& e);

		bool OnWindowResize(WindowResizeEvent& e);


		LayerStack m_LayerStack;
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
	};
}

