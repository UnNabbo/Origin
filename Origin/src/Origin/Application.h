#pragma once

#include "Core.h"
#include "Platform\Windows\WindowsWindow.h"

namespace Origin {
	class ORIGIN_API Application {
	public:
		Application();

		~Application();

		virtual void OnStart();

		virtual void OnUpdate();

		void Run();
	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
	};
}

