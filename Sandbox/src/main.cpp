#include "Origin.h"

class Example : public Origin::Layer {
public:
	Example()
		: Layer("Example") {
	}

	void OnUpdate() override {

	}

	void OnEvent(Origin::Event& e) override {

	}
};

class Sandbox : public Origin::Application {
public:

	Sandbox() {
		PushLayer(new Example);
		PushOverlay(new Origin::ImGuiLayer);
	}

	~Sandbox() {

	}
};



Origin::Application* CreateApplication() {
	return new Sandbox;
}