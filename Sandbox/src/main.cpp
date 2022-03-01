#include "Origin.h"
#include "ImGui/imgui.h"

#include "Origin/Renderer/Utility/Camera.h"

#include <glm/gtc/matrix_transform.hpp>

#include "GLFW/glfw3.h"

#include <glm/gtc/type_ptr.hpp>

class Example : public Origin::Layer {
public:
	Example()
		: Layer("Example") {
		shader = Origin::Shader::Create(
			"E:/DEV/Origin/Origin/asset/Shader.glsl");


		float square_vertices[4 * 5] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
		};


		uint32_t  square_indices[] = {
			0,1,2,2,3,0
		};

		Origin::BufferLayout layout = {
			{Origin::ShaderDataType::Float3, "a_Position"},
			{Origin::ShaderDataType::Float2, "a_TexCoord"},

		};

		square_VAO = Origin::VertexArray::Create();

		Origin::AssetRef<Origin::VertexBuffer> square_VBO = Origin::VertexBuffer::Create(square_vertices, sizeof(square_vertices));
		square_VBO->SetLayout(layout);

		Origin::AssetRef<Origin::IndexBuffer> square_IBO = Origin::IndexBuffer::Create(square_indices, sizeof(square_indices));
		
		square_VAO->AddVertexBuffer(square_VBO);
		square_VAO->SetIndexBuffer(square_IBO);

		Texture2D = Origin::Texture2D::Create("E:/DEV/Origin/Origin/asset/images/milky-way-full-stars-space.jpg");

		shader->UploadUniform("u_Texture", 0);
		
	}


	void OnUpdate() override {
		Origin::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		Origin::RenderCommand::Clear();

		Origin::Renderer::BeginScene(camera);

		Texture2D->Bind(0);
		Origin::Renderer::Submit(square_VAO, shader);
		
		Origin::Renderer::EndScene();

	}

	void OnImGuiRender() override{
		ImGui::Begin("Slider");

		static float value[3] = { 0,0,0 };
		static float value1[3] = { 0,0,0 };

		static bool check = 0;

		ImGui::SliderFloat3("Rotation", value, -180, 180);
		ImGui::SliderFloat3("Position", value1, -10.0f, 10.0f);
		ImGui::Checkbox("Reset", &check);
		if (check) {
			value[0] = 0;
			value[1] = 0;
			value[2] = 0;
			value1[0] = 0;
			value1[1] = 0;
			value1[2] = 0;
			check = 0;
		}
		camera.SetRotation({ value[0] / 3, value[1] / 3, value[2] / 3 });
		camera.SetPosition({ value1[0], value1[1], value1[2] });


		ImGui::End();
	}

	void OnEvent(Origin::Event& e) override {

	}
private:
	Origin::AssetRef<Origin::VertexArray> VAO;
	Origin::AssetRef<Origin::VertexBuffer> VBO;
	Origin::AssetRef<Origin::IndexBuffer> IBO;
	Origin::AssetRef<Origin::Shader> shader;
	Origin::AssetRef<Origin::Texture2D> Texture2D;

	Origin::Camera camera = (Origin::CameraTypes::Orthographic);

	Origin::AssetRef<Origin::VertexArray> square_VAO;
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