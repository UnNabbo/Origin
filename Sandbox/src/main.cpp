#include "Origin.h"
#include "ImGui\imgui.h"



class Example : public Origin::Layer {
public:
	Example()
		: Layer("Example") {
	}

	void OnUpdate() override {

	}

	void OnImGuiRender() override{
		
		ImGui::Begin("TEXT");
		ImGui::Text("DIO");
		ImGui::End();

	}

	void OnEvent(Origin::Event& e) override {

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