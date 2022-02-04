#pragma once

#include "Core.h"

#include "Events/InputEvents.h"

#include "Platform/Windows/WindowsWindow.h"
#include "Events/ApplicationEvents.h"

namespace Origin {
	class ORIGIN_API Application {
	public:
		Application();

		~Application();

		virtual void OnStart();

		virtual void OnUpdate();

		void OnEvents(Event& e);

		void Run();
	private:
		bool OnKeyPress(KeyPressedEvent& e);

		bool OnMouseMove(MouseMovedEvent& e);

		bool OnWindowClose(WindowCloseEvent& e);

		bool OnWindowResize(WindowResizeEvent& e);



		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
	};
}

