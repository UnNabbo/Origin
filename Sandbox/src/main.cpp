#include "Origin.h"
#include "ImGui/imgui.h"

#include "Origin/Renderer/Utility/Camera/CameraControllers/EditorCamera.h"

#include <glm/gtc/matrix_transform.hpp>

#include "GLFW/glfw3.h"

#include <glm/gtc/type_ptr.hpp>

class Example : public Origin::Layer {
public:
	Example()
		: Layer("Example") {

		shader = Origin::Shader::Create(("E:/DEV/Origin/Origin/asset/Shader.glsl"));
		

		float square_vertices[] = {
			-0.5f, -0.5f,  0.5f, 0.0f, 0.0f,
			 0.5f, -0.5f,  0.5f, 1.0f, 0.0f,
			 0.5f,  0.5f,  0.5f, 1.0f, 1.0f,
			-0.5f,  0.5f,  0.5f, 0.0f, 1.0f,

			-0.5f, -0.5f,  0.5f, 0.0f, 0.0f,
			-0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
			-0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
			-0.5f,  0.5f,  0.5f, 0.0f, 1.0f,

			-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
			 0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
			 0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
			-0.5f,  0.5f, -0.5f, 0.0f, 1.0f,

			-0.5f,  0.5f, -0.5f, 0.0f, 0.0f,
			 0.5f,  0.5f, -0.5f, 1.0f, 0.0f,
			 0.5f,  0.5f,  0.5f, 1.0f, 1.0f,
			-0.5f,  0.5f,  0.5f, 0.0f, 1.0f,

			 0.5f, -0.5f,  0.5f, 0.0f, 0.0f,
			 0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
			 0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
			 0.5f,  0.5f,  0.5f, 0.0f, 1.0f,

			-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
			 0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
			 0.5f, -0.5f,  0.5f, 1.0f, 1.0f,
			-0.5f, -0.5f,  0.5f, 0.0f, 1.0f,



		};


		uint32_t  square_indices[] = {
			0,1,2,2,3,0,
			4,5,6,6,7,4,
			8,9,10,10,11,8,
			12,13,14,14,15,12,
			16,17,18,18,19,16,
			20,21,22,22,23,20


		};
			
		Origin::BufferLayout layout = {
			{Origin::ShaderDataType::Float3, "a_Position"},
			{Origin::ShaderDataType::Float2, "a_TexCoord"},

		};

		square_VAO = Origin::VertexArray::Create("SquareVAO");

		Origin::Reference<Origin::VertexBuffer> square_VBO = Origin::VertexBuffer::Create();
		square_VBO->SetLayout(layout);

		Origin::Reference<Origin::IndexBuffer> square_IBO = Origin::IndexBuffer::Create();
		
		

		square_VBO->SetData(square_vertices, sizeof(square_vertices));
		square_IBO->SetData(square_indices, sizeof(square_indices));

		square_VAO->AddVertexBuffer(square_VBO);
		square_VAO->SetIndexBuffer(square_IBO);
		
		shader->UploadUniform("u_Texture", 0);


	}


	void OnUpdate() override {
		camera.OnUpdate();

		Origin::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		Origin::RenderCommand::Clear();

		Origin::Renderer::BeginScene(camera);

		shader->UploadUniform("u_time", Origin::Time::GetTime());
		Origin::Renderer::Submit(square_VAO, shader);

		Origin::Renderer::EndScene();

	}


	void OnImGuiRender() override{
		ImGui::Begin("Settings");

		static bool check1 = 0;

		ImGui::Checkbox("Reload", &check1);

		if (check1) {
			shader->Reload();
			check1 = 0;
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
	Origin::Reference<Origin::VertexArray> square_VAO;
	Origin::Reference<Origin::Shader> shader;

	Origin::EditorCamera camera = Origin::EditorCamera(45.0f, 1280.0f/720.0f, 0.1f, 1000.0f);

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