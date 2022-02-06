#include "Origin.h"

class Example : public Origin::Layer {
public:
	Example()
		: Layer("Example") {
	}

	void OnUpdate() override {
		ORIGIN_INFO("Example");
	}

	void OnEvent(Origin::Event& e) override {
		ORIGIN_INFO("Event");
	}
};

class Sandbox : public Origin::Application {
public:

	Sandbox() {
		PushLayer(new Example);
	}

	~Sandbox() {

	}
};



Origin::Application* CreateApplication() {
	return new Sandbox;
}