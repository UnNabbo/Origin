#include "OGpch.h"

#include "Renderer.h"

namespace Origin {

	Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData;

	void Renderer::Init() {
		RenderCommand::Init();
	}

	void Renderer::BeginScene(Camera& camera) {
		m_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void Renderer::EndScene() {

	}

	void Renderer::Submit(AssetRef<VertexArray>& vertexArray, AssetRef<Shader>& shader, glm::mat4& model) {
		
		shader->UploadUniform("u_ProjectionView", m_SceneData->ViewProjectionMatrix);
		shader->UploadUniform("u_Model", model);

		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}

}