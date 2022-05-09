#include "OGpch.h"

#include "Renderer.h"
#include "Renderer2D.h"


namespace Origin {

	Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData;

	void Renderer::Init() {
		RenderCommand::Init();
		Renderer2D::Init();
	}

	void Renderer::ResizeWindow(uint32_t width, uint32_t height) {
		RenderCommand::ResizeWindow(width, height);
	}

	void Renderer::BeginScene(Camera& camera) {
		//m_SceneData->ViewProjectionMatrix = camera.GetViewProjection();
	}

	void Renderer::EndScene() {

	}

	void Renderer::Submit(Reference<VertexArray>& vertexArray, Reference<Shader>& shader, glm::mat4& model) {
		
		shader->UploadUniform("u_ProjectionView", m_SceneData->ViewProjectionMatrix);
		shader->UploadUniform("u_Model", model);

		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}

}