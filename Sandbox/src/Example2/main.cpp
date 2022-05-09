
#include "Origin.h"
#include <Origin/Core/EntryPoint.h>

#include "ImGui/imgui.h"

#include "Bird/Bird.h"
#include "Pipe/Pipe.h"
#include "Random\Random.h"

class Game : public Origin::Layer {
public:
	Game() : Layer("Game"){}
		
	void OnAttach() override {
		pipe1.SetSize(pipe1.GetSize() * glm::vec2(1, -1));
		pipe1.SetPosition(pipe1.GetPosition() * glm::vec3(1, -1, 1));
	}

	void OnUpdate() override {
		Origin::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		Origin::RenderCommand::Clear();

		Origin::Renderer2D::BeginScene(camera);
		uint32_t offset;
		pipe.DrawPipe();
		pipe1.DrawPipe();
		Origin::Renderer2D::DrawRotatedQuad(bird.GetPosition(), bird.GetRotation(), bird.GetSize(), bird.GetTexture());


		bird.Update();
	
			pipe.Update(offset);
			pipe1.Update(offset);

		camera.SetPosition(camera.GetPosition() + glm::vec3(0, 0, 0.2));
		Origin::Renderer2D::EndScene();


	}

	void OnEvent(Origin::Event& e) override {

	}

private:
	bool lost = 0;

	float width = Origin::Application::Get().GetWindow().GetWidth();
	float height = Origin::Application::Get().GetWindow().GetHeight();

	
	Pipe pipe = Pipe(Origin::Texture2D::Create("E:/DEV/Origin/Sandbox/src/Example1/res/pipe.png"));
	Pipe pipe1 = Pipe(Origin::Texture2D::Create("E:/DEV/Origin/Sandbox/src/Example1/res/pipe.png"));


	Bird bird = Bird(Origin::Texture2D::Create("E:/DEV/Origin/Sandbox/src/Example1/res/bird.png"));
	Origin::OrthographicCamera camera = Origin::OrthographicCamera(-width / 100.0f, width / 100.0f, -height / 100.0f, height / 100.0f);
};

class App : public Origin::Application {
public:

	App() {
		PushLayer(new Game);
	}

	~App() {

	}
};



Origin::Application* CreateApplication() {
	return new App;
}