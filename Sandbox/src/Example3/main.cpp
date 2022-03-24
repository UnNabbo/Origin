#define OG_ENTRYPOINT
#include "Origin.h"
#include "ImGui/imgui.h"

class Example : public Origin::Layer {
public:
	Example() : Layer("Example") {}

	void OnAttach() override {
		texture = Origin::Texture2D::Create("E:/DEV/Origin/Origin/asset/images/Amogus.png");
	}

	void OnUpdate() override {
		camera.OnUpdate();

		Origin::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		Origin::RenderCommand::Clear();

		Origin::Renderer2D::BeginScene(camera);

		for (float i = 0; i < 50; i++)
			for (float j = 0; j < 50; j++) {
				Origin::Renderer2D::DrawQuad({i- 50/2.0f,j - 50/2.0f}, { 1,1 }, { 1,0,0,1 });

			}

		//Origin::Renderer2D::DrawQuad({ sqrt(ka),sqrt(ka),0 }, { 1,1 }, texture);

		Origin::Renderer2D::EndScene();

	}


	void OnImGuiRender() override {
	
		ImGui::Begin("FPS");

		ImGui::Text("FPS: %f\nMS: %f", 1 / Origin::Time::GetSeconds(), Origin::Time::GetMilliseconds());

		ImGui::End();

	}

	void OnEvent(Origin::Event& e) override {
		camera.OnEvent(e);
	}
private:
	Origin::Reference<Origin::Texture2D> texture;
	Origin::Reference<Origin::SubTexture2D> subtexture;


	int ka = 1;
	Origin::EditorCamera camera = Origin::EditorCamera(45.0f, 1280.0f / 720.0f, 0.001f, 1000.0f);

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