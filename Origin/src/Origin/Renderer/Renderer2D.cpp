#include "OGpch.h"

#include "Renderer2D.h"

#include "Origin/Core/Math/Math.h"

#include "Primitives/VertexArray.h"
#include "Primitives/Buffers.h"

#include "RenderCommand.h"
#include "Primitives/Shader.h"

namespace Origin {
	struct Renderer2DData {
		Reference<VertexArray> QuadVAO;
		Reference<Shader> QuadShader;
		Reference<Texture2D> QuadTexture;
	};

	static Renderer2DData s_Data;

	void Renderer2D::Init() {
		
		s_Data.QuadVAO = VertexArray::Create("QuadVAO");

		float quadVertices[] = {
			-0.5f, -0.5f,  0.5f, 0.0f, 0.0f,
			 0.5f, -0.5f,  0.5f, 1.0f, 0.0f,
			 0.5f,  0.5f,  0.5f, 1.0f, 1.0f,
			-0.5f,  0.5f,  0.5f, 0.0f, 1.0f,
		};

		uint32_t  quadIndices[] = {
			0,1,2,2,3,0,
		};

		Reference<VertexBuffer> QuadVBO = VertexBuffer::Create(quadVertices, sizeof(quadVertices));
		BufferLayout layout = {
			{ShaderDataType::Float3, "a_Position"},
			{ShaderDataType::Float2, "a_TexCoord"},
		};
		QuadVBO->SetLayout(layout);

		Reference<IndexBuffer> QuadIBO = IndexBuffer::Create(quadIndices, sizeof(quadIndices));

		s_Data.QuadVAO->AddVertexBuffer(QuadVBO);
		s_Data.QuadVAO->SetIndexBuffer(QuadIBO);

		s_Data.QuadTexture = Texture2D::Create(1, 1);
		uint32_t texture = 0xffffffff;
		s_Data.QuadTexture->SetData(&texture, 1);

		s_Data.QuadShader = Shader::Create("E:/DEV/Origin/Origin/asset/Shader.glsl");
	}

	void Renderer2D::Shutdown() {
	}

	void Renderer2D::BeginScene(Camera& camera) {
		s_Data.QuadVAO->Bind();
		s_Data.QuadShader->Bind();
		s_Data.QuadShader->UploadUniform("u_ProjectionView", camera.GetViewProjection());
	}

	
	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color) {
		DrawQuad({ position.x, position.y, 0.0f }, size, color);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color) {
		DrawQuad(position, size, color, s_Data.QuadTexture);
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Reference<Texture2D>& texture) {
		DrawQuad({ position.x, position.y, 0.0f }, size, texture);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Reference<Texture2D>& texture) {
		DrawQuad(position, size, {1.0f, 1.0f, 1.0f, 1.0f}, texture);
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color, const Reference<Texture2D>& texture) {
		DrawQuad({ position.x, position.y, 0.0f }, size, color, texture);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color, const Reference<Texture2D>& texture) {
		s_Data.QuadShader->UploadUniform("u_Color", color);
		texture->Bind(0);

		glm::mat4 model = glm::translate(glm::mat4(1), position)
			* 1.0f
			* glm::scale(glm::mat4(1), { size.x, size.y, 0.0f });

		s_Data.QuadShader->UploadUniform("u_Model", model);

		RenderCommand::DrawIndexed(s_Data.QuadVAO);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec3& rotation, const glm::vec2& size, const glm::vec4& color) {
		DrawRotatedQuad({ position.x, position.y, 0.0f }, rotation, size, color);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec3& rotation, const glm::vec2& size, const glm::vec4& color) {
		DrawRotatedQuad(position, rotation, size, color, s_Data.QuadTexture);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec3& rotation, const glm::vec2& size, const Reference<Texture2D>& texture) {
		DrawRotatedQuad({ position.x, position.y, 0.0f }, rotation, size, texture);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec3& rotation, const glm::vec2& size, const Reference<Texture2D>& texture) {
		DrawRotatedQuad(position, rotation, size, { 1.0f, 1.0f, 1.0f, 1.0f }, texture);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec3& rotation, const glm::vec2& size, const glm::vec4& color, const Reference<Texture2D>& texture) {
		DrawRotatedQuad({ position.x, position.y, 0.0f }, rotation, size, color, texture);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec3& position,const glm::vec3& rotation, const glm::vec2& size, const glm::vec4& color, const Reference<Texture2D>& texture) {
		s_Data.QuadShader->UploadUniform("u_Color", color);
		texture->Bind(0);

		glm::mat4 model = glm::translate(glm::mat4(1), position)
			* glm::toMat4(EulerToQuat(rotation))
			* glm::scale(glm::mat4(1), { size.x, size.y, 0.0f });

		s_Data.QuadShader->UploadUniform("u_Model", model);

		RenderCommand::DrawIndexed(s_Data.QuadVAO);
	}

	void Renderer2D::EndScene() {
	
	}
}