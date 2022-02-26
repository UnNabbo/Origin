#include "OGpch.h"

#include "Renderer.h"

namespace Origin {

	Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData;

	void Renderer::BeginScene(Camera& camera) {
		m_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void Renderer::EndScene() {

	}

	void Renderer::Submit(std::shared_ptr<VertexArray>& vertexArray, std::shared_ptr<Shader>& shader) {
		
		shader->UploadUniform("u_ProjectionView", m_SceneData->ViewProjectionMatrix);
		
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}

}