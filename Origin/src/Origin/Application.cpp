#include "Application.h"

namespace Origin {

	Application::Application(){

	}

	Application::~Application() {

	}

	void Application::OnStart() {}

	void Application::OnUpdate() {}

	void Application::Run() {
		OnStart();
		while (true) {
			OnUpdate();
		}
	}
}