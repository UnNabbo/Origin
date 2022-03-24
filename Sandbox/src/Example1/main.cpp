#define OG_ENTRYPOINT
#include "Origin.h"
#include "ImGui/imgui.h"

#include "Origin/Renderer/Utility/Camera/CameraControllers/EditorCamera.h"

#include "Origin/Core/ResourceManager/AssetPool.h"

class Example : public Origin::Layer {
public:
	Example(): Layer("Example") {}

	void OnAttach() override {
		textureAtlas = Origin::TextureAtlas::Create("E:/DEV/Origin/Origin/asset/images/S9OtX.jpg", {16,16});
		texture = Origin::Texture2D::Create("E:/DEV/Origin/Origin/asset/images/Amogus.png");

		subtexture = textureAtlas->GetSubTexture({6,6}, {2,1});
		subtexture1 = textureAtlas->GetSubTexture({ 0,14 }, { 1,1 });
		subtexture2 = textureAtlas->GetSubTexture({ 6,7 }, { 2,1 });

	}

	void OnUpdate() override {
		camera.OnUpdate();

		Origin::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		Origin::RenderCommand::Clear();

		Origin::Renderer2D::BeginScene(camera);
		
	

		Origin::Renderer2D::DrawQuad({ 0,0,0 }, { 2,1 }, subtexture);
		Origin::Renderer2D::DrawQuad({ 0,1,0 }, { 1,1 }, subtexture1);
		Origin::Renderer2D::DrawQuad({ 0,3,0 }, { 1,1 }, texture);

		Origin::Renderer2D::DrawQuad({ 0,2,0 }, { 2,1 }, subtexture2);

		Origin::Renderer2D::EndScene();

	}


	void OnImGuiRender() override{
		ImGui::Begin("Settings");

		auto stats = Origin::Renderer2D::GetStats();

		ImGui::Text("Renderer2D Stats: \n");
		ImGui::Text("DrawCall: %i\nQuad Drawn: %i\nTexture Used: %i", stats.DrawCalls, stats.QuadDrawn, stats.TextureUsed);


		static bool check = 1;
		static bool check1 = 0;
		static bool check2 = 0;

		ImGui::SliderInt("Qaud", &ka, 1, 16384*100);

		ImGui::Checkbox("Camera Mode", &check);
		ImGui::Checkbox("WireFrame View", &check1);
		check2 = ImGui::Button("Reload Shaders", ImVec2(128,32));



		Origin::RenderCommand::SetWireFrameView(check1);
		camera.setOrthographic(check);

		if (check2) {
			for (auto& shader : Origin::ShaderAssetPool::RetriveIterator()) {
				shader.second->Reload();
			}
			Origin::Renderer2D::ReloadSamplers();
		}
	

		ImGui::End();


		ImGui::Begin("FPS");

		ImGui::Text("FPS: %f\nMS: %f", 1 / Origin::Time::GetSeconds(), Origin::Time::GetMilliseconds());

		ImGui::End();

	}

	void OnEvent(Origin::Event& e) override {
		camera.OnEvent(e);
	}
private:
	Origin::Reference<Origin::Texture2D> texture;
	Origin::Reference<Origin::TextureAtlas> textureAtlas;

	Origin::Reference<Origin::SubTexture2D> subtexture;
	Origin::Reference<Origin::SubTexture2D> subtexture1;
	Origin::Reference<Origin::SubTexture2D> subtexture2;



	int ka = 1;
	Origin::EditorCamera camera = Origin::EditorCamera(45.0f, 1280.0f/720.0f, 0.001f, 1000.0f);

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