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
		shader.reset(Origin::Shader::Create("E:/DEV/Origin/Origin/asset/Vertex.shader", "E:/DEV/Origin/Origin/asset/Fragment.shader"));

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
		};

		float square_vertices[4 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
			 0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
			-0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
		};

		uint32_t indices[] = {
			0,1,2,
		};

		uint32_t  square_indices[] = {
			0,1,2,2,3,0
		};

		Origin::BufferLayout layout = {
			{Origin::ShaderDataType::Float3, "a_Position"},
			{Origin::ShaderDataType::Float4, "a_Color"},

		};

		VAO.reset(Origin::VertexArray::Create());
		VBO.reset(Origin::VertexBuffer::Create(vertices, sizeof(vertices)));
		IBO.reset(Origin::IndexBuffer::Create(indices, sizeof(indices)));

		shader->Bind();

		VBO->SetLayout(layout);

		VAO->AddVertexBuffer(VBO);
		VAO->SetIndexBuffer(IBO);

		square_VAO.reset(Origin::VertexArray::Create());

		std::shared_ptr<Origin::VertexBuffer> square_VBO;
		square_VBO.reset(Origin::VertexBuffer::Create(square_vertices, sizeof(square_vertices)));
		square_VBO->SetLayout(layout);

		std::shared_ptr<Origin::IndexBuffer> square_IBO;
		square_IBO.reset(Origin::IndexBuffer::Create(square_indices, sizeof(square_indices)));
		
		square_VAO->AddVertexBuffer(square_VBO);
		square_VAO->SetIndexBuffer(square_IBO);

	}

	void OnUpdate() override {
		Origin::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		Origin::RenderCommand::Clear();

		Origin::Renderer::BeginScene(camera);



		Origin::Renderer::Submit(square_VAO, shader);
		Origin::Renderer::Submit(VAO,shader);
		
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
		camera.SetRotation({ value[0], value[1], value[2] });
		camera.SetPosition({ value1[0], value1[1], value1[2] });


		ImGui::End();
	}

	void OnEvent(Origin::Event& e) override {

	}
private:
	std::shared_ptr<Origin::VertexArray> VAO;
	std::shared_ptr<Origin::VertexBuffer> VBO;
	std::shared_ptr<Origin::IndexBuffer> IBO;
	std::shared_ptr<Origin::Shader> shader;

	Origin::Camera camera = (Origin::CameraTypes::Orthographic);

	std::shared_ptr<Origin::VertexArray> square_VAO;
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