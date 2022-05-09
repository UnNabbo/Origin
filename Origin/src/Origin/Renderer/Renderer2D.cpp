#include "OGpch.h"
#include "Renderer2D.h"
#include "Origin/Core/Math/Math.h"
#include "Origin/Scene/Entity.h"
#include "glm/gtc/quaternion.hpp"
#include "glm/gtx/quaternion.hpp"

namespace Origin {

	struct QuadVertex {
		glm::vec3 Position;
		glm::vec4 Color;
		glm::vec2 TexCoord;
		float TexIndex;
		float TilingFactor;
	};

	struct Renderer2DData {
		static const uint32_t MaxQuads = 16384;
		static const uint32_t MaxVertices = MaxQuads * 4;
		static const uint32_t MaxIndices = MaxQuads * 6;
		static const uint32_t MaxTextureSlots = 32; // TODO: RenderCaps

		Reference<VertexArray> QuadVAO;
		Reference<VertexBuffer> QuadVBO;
		Reference<Shader> QuadShader;
		Reference<Shader> GridShader;
		Reference<Texture2D> QuadDefaultTexture;

		uint32_t QuadIndexCount = 0;
		QuadVertex* QuadVertexBufferBase = nullptr;
		QuadVertex* QuadVertexBufferPtr = nullptr;

		std::array<Reference<Texture2D>, MaxTextureSlots> TextureSlots;
		uint32_t TextureSlotIndex = 0; // 0 = white texture

		glm::vec4 QuadVertexPositions[4];

		Renderer2D::Statistics Stats;
	};

	static Renderer2DData s_Data;

	void Renderer2D::Init() {
		s_Data.QuadVAO = VertexArray::Create("QuadVAO");

		s_Data.QuadVBO = VertexBuffer::Create(s_Data.MaxVertices * sizeof(QuadVertex));
		s_Data.QuadVBO->SetLayout({
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float4, "a_Color" },
			{ ShaderDataType::Float2, "a_TexCoord" },
			{ ShaderDataType::Float, "a_TexIndex" },
			{ ShaderDataType::Float, "a_TilingFactor" }
			});
		s_Data.QuadVAO->AddVertexBuffer(s_Data.QuadVBO);

		s_Data.QuadVertexBufferBase = new QuadVertex[s_Data.MaxVertices];

		uint32_t* quadIndices = new uint32_t[s_Data.MaxIndices];

		uint32_t offset = 0;
		for (uint32_t i = 0; i < s_Data.MaxIndices; i += 6) {
			quadIndices[i + 0] = offset + 0;
			quadIndices[i + 1] = offset + 1;
			quadIndices[i + 2] = offset + 2;

			quadIndices[i + 3] = offset + 2;
			quadIndices[i + 4] = offset + 3;
			quadIndices[i + 5] = offset + 0;

			offset += 4;
		}

		Reference<IndexBuffer> quadIB = IndexBuffer::Create(quadIndices, s_Data.MaxIndices * sizeof(uint32_t));
		s_Data.QuadVAO->SetIndexBuffer(quadIB);
		delete[] quadIndices;

		s_Data.QuadDefaultTexture = Texture2D::Create(1, 1);
		uint32_t whiteTextureData = 0xffffffff;
		s_Data.QuadDefaultTexture->SetData(&whiteTextureData, sizeof(uint32_t));

		int32_t samplers[s_Data.MaxTextureSlots];
		for (uint32_t i = 0; i < s_Data.MaxTextureSlots; i++)
			samplers[i] = i;

		s_Data.GridShader = Shader::Create("E:/DEV/Origin/Origin/asset/Grid.glsl");
		s_Data.GridShader->Bind();
		s_Data.QuadShader = Shader::Create("E:/DEV/Origin/Origin/asset/Shader.glsl");
		s_Data.QuadShader->Bind();
		s_Data.QuadShader->UploadUniform("u_Textures", samplers, s_Data.MaxTextureSlots);

		s_Data.TextureSlots[0] = s_Data.QuadDefaultTexture;

		s_Data.QuadVertexPositions[0] = { -0.5f, -0.5f, 0.0f, 1.0f };
		s_Data.QuadVertexPositions[1] = {  0.5f, -0.5f, 0.0f, 1.0f };
		s_Data.QuadVertexPositions[2] = {  0.5f,  0.5f, 0.0f, 1.0f };
		s_Data.QuadVertexPositions[3] = { -0.5f,  0.5f, 0.0f, 1.0f };
	}

	void Renderer2D::Shutdown() {
		delete[] s_Data.QuadVertexBufferBase;
	}

	void Renderer2D::BeginScene(Scene& scene, bool showGrid) {
		ResetStats();
		StartBatch();

		glm::mat4 ViewMatrix;
		ViewMatrix = glm::inverse(glm::translate(glm::mat4(1), -scene.GetMainCamera()->GetComponent<TransformComponent>().Position) * glm::toMat4(EulerToQuat(scene.GetMainCamera()->GetComponent<TransformComponent>().Rotation)));
		
		s_Data.QuadShader->Bind();
		s_Data.QuadShader->UploadUniform("u_ProjectionView",  glm::mat4(scene.GetMainCamera()->GetComponent<CameraComponent>()) * ViewMatrix);
		StartBatch();
	}

	void Renderer2D::BeginScene(EditorCamera& camera) {
		ResetStats();
		StartBatch();

		s_Data.QuadShader->Bind();
		s_Data.QuadShader->UploadUniform("u_ProjectionView", camera.GetViewProjection());
	}


	void Renderer2D::ReloadSamplers() {
		s_Data.QuadShader->Bind();

		int32_t samplers[s_Data.MaxTextureSlots];
		for (uint32_t i = 0; i < s_Data.MaxTextureSlots; i++)
			samplers[i] = i;

		s_Data.QuadShader->UploadUniform("u_Textures", samplers, s_Data.MaxTextureSlots);

	}

	void Renderer2D::EndScene() {
		uint32_t dataSize = (uint32_t)((uint8_t*)s_Data.QuadVertexBufferPtr - (uint8_t*)s_Data.QuadVertexBufferBase);
		s_Data.QuadVBO->SetData(s_Data.QuadVertexBufferBase, dataSize);

		Flush();
	}

	void Renderer2D::StartBatch() {
		s_Data.QuadIndexCount = 0;
		s_Data.QuadVertexBufferPtr = s_Data.QuadVertexBufferBase;

		s_Data.TextureSlotIndex = 1;
	}

	void Renderer2D::Flush() {
		if (s_Data.QuadIndexCount == 0)
			return; 

		for (uint32_t i = 0; i < s_Data.TextureSlotIndex; i++)
			s_Data.TextureSlots[i]->Bind(i);

		RenderCommand::DrawIndexed(s_Data.QuadVAO, s_Data.QuadIndexCount);
		s_Data.Stats.DrawCalls++;
	}

	void Renderer2D::NextBatch() {
		uint32_t dataSize = (uint32_t)((uint8_t*)s_Data.QuadVertexBufferPtr - (uint8_t*)s_Data.QuadVertexBufferBase);
		s_Data.QuadVBO->SetData(s_Data.QuadVertexBufferBase, dataSize);
		Flush();
		StartBatch();
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color) {
		DrawQuad({ position.x, position.y, 0.0f }, size, s_Data.QuadDefaultTexture, color);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color) {
		DrawQuad(position, size, s_Data.QuadDefaultTexture, color);
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Reference<Texture2D>& texture, const glm::vec4& color) {
		DrawQuad({ position.x, position.y, 0.0f }, size, texture, color);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Reference<Texture2D>& texture, const glm::vec4& color) {

		constexpr size_t quadVertexCount = 4;

		constexpr glm::vec2 textureCoords[] = { { 0, 0 }, { 1, 0 }, { 1, 1 }, { 0, 1 } };
		constexpr glm::vec4 colr[] = { { 1.0f, 0.0f,0.0f,1.0f }, { 0.0f, 1.0f,0.0f,1.0f }, { 0.0f, 0.0f,1.0f,1.0f }, { 1.0f, 1.0f,0.0f,1.0f } };

		if (s_Data.QuadIndexCount >= Renderer2DData::MaxIndices)
			NextBatch();

		float textureIndex = 0.0f;
		for (uint32_t i = 1; i < s_Data.TextureSlotIndex; i++) {
			if (s_Data.TextureSlots[i].get() == texture.get()) {
				textureIndex = (float)i;
				break;
			}
		}

		if (textureIndex == 0.0f) {
			if (s_Data.TextureSlotIndex >= Renderer2DData::MaxTextureSlots)
				NextBatch();

			textureIndex = (float)s_Data.TextureSlotIndex;
			s_Data.TextureSlots[s_Data.TextureSlotIndex] = texture;
			s_Data.TextureSlotIndex++;
			s_Data.Stats.TextureUsed++;
		}
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		for (size_t i = 0; i < quadVertexCount; i++) {
			s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPositions[i];
			s_Data.QuadVertexBufferPtr->Color = colr[i];
			s_Data.QuadVertexBufferPtr->TexCoord = textureCoords[i];
			s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
			s_Data.QuadVertexBufferPtr++;
		}

		s_Data.QuadIndexCount += 6;

		s_Data.Stats.QuadDrawn++;
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Reference<SubTexture2D>& texture, const glm::vec4& color) {
		DrawQuad({ position.x, position.y, 0.0f }, size, texture, color);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Reference<SubTexture2D>& texture, const glm::vec4& color) {

		constexpr size_t quadVertexCount = 4;
		glm::vec2 begin = texture->GetBegin();
		glm::vec2 end = texture->GetEnd();


		const glm::vec2 textureCoords[] = { { begin.x, begin.y }, { end.x, begin.y }, { end.x, end.y }, { begin.x, end.y } };

		if (s_Data.QuadIndexCount >= Renderer2DData::MaxIndices)
			NextBatch();

		float textureIndex = 0.0f;
		for (uint32_t i = 1; i < s_Data.TextureSlotIndex; i++) {
			if (*s_Data.TextureSlots[i].get() == *texture->GetTexture().get()) {
				textureIndex = (float)i;
				break;
			}
		}

		if (textureIndex == 0.0f) {
			if (s_Data.TextureSlotIndex >= Renderer2DData::MaxTextureSlots)
				NextBatch();

			textureIndex = (float)s_Data.TextureSlotIndex;
			s_Data.TextureSlots[s_Data.TextureSlotIndex] = texture->GetTexture();
			s_Data.TextureSlotIndex++;
			s_Data.Stats.TextureUsed++;
		}
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		for (size_t i = 0; i < quadVertexCount; i++) {
			s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPositions[i];
			s_Data.QuadVertexBufferPtr->Color = color;
			s_Data.QuadVertexBufferPtr->TexCoord = textureCoords[i];
			s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
			s_Data.QuadVertexBufferPtr++;
		}

		s_Data.QuadIndexCount += 6;

		s_Data.Stats.QuadDrawn++;
	}


	void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec3& rotation, const glm::vec2& size, const glm::vec4& color) {
		DrawRotatedQuad({ position.x, position.y, 0.0f }, rotation, size, s_Data.QuadDefaultTexture, color);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec3& rotation, const glm::vec2& size, const glm::vec4& color) {
		DrawRotatedQuad(position, rotation, size, s_Data.QuadDefaultTexture, color);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec3& rotation, const glm::vec2& size, const Reference<Texture2D>& texture, const glm::vec4& color) {
		DrawRotatedQuad({ position.x, position.y, 0.0f }, rotation, size, texture, color);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec3& rotation, const glm::vec2& size, const Reference<Texture2D>& texture, const glm::vec4& color) {
		if (rotation == glm::vec3(0, 0, 0)) {
			DrawQuad(position,size,texture,color);
			return;
		}

		constexpr size_t quadVertexCount = 4;
		constexpr glm::vec2 textureCoords[] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };

		if (s_Data.QuadIndexCount >= Renderer2DData::MaxIndices)
			NextBatch();

		float textureIndex = 0.0f;
		for (uint32_t i = 1; i < s_Data.TextureSlotIndex; i++) {
			if (*s_Data.TextureSlots[i].get() == *texture.get()) {
				textureIndex = (float)i;
				break;
			}
		}

		if (textureIndex == 0.0f) {
			if (s_Data.TextureSlotIndex >= Renderer2DData::MaxTextureSlots)
				NextBatch();

			textureIndex = (float)s_Data.TextureSlotIndex;
			s_Data.TextureSlots[s_Data.TextureSlotIndex] = texture;
			s_Data.TextureSlotIndex++;
		}

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::toMat4(EulerToQuat(rotation))
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		for (size_t i = 0; i < quadVertexCount; i++) {
			s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPositions[i];
			s_Data.QuadVertexBufferPtr->Color = color;
			s_Data.QuadVertexBufferPtr->TexCoord = textureCoords[i];
			s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
			s_Data.QuadVertexBufferPtr++;
		}

		s_Data.QuadIndexCount += 6;

		s_Data.Stats.QuadDrawn++;
	}

	void Renderer2D::DrawQuad(glm::mat4 transform, const glm::vec4& color) {
		DrawQuad(transform, s_Data.QuadDefaultTexture, color);
	}

	void Renderer2D::DrawQuad(glm::mat4 transform, const Reference<Texture2D>& texture, const glm::vec4& color) {
		constexpr size_t quadVertexCount = 4;
		constexpr glm::vec2 textureCoords[] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };



		if (s_Data.QuadIndexCount >= Renderer2DData::MaxIndices)
			NextBatch();

		float textureIndex = 0.0f;
		for (uint32_t i = 1; i < s_Data.TextureSlotIndex; i++) {
			if (*s_Data.TextureSlots[i].get() == *texture.get()) {
				textureIndex = (float)i;
				break;
			}
		}

		if (textureIndex == 0.0f) {
			if (s_Data.TextureSlotIndex >= Renderer2DData::MaxTextureSlots)
				NextBatch();

			textureIndex = (float)s_Data.TextureSlotIndex;
			s_Data.TextureSlots[s_Data.TextureSlotIndex] = texture;
			s_Data.TextureSlotIndex++;
		}

		for (size_t i = 0; i < quadVertexCount; i++) {
			s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPositions[i];
			s_Data.QuadVertexBufferPtr->Color = color;
			s_Data.QuadVertexBufferPtr->TexCoord = textureCoords[i];
			s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
			s_Data.QuadVertexBufferPtr++;
		}

		s_Data.QuadIndexCount += 6;

		s_Data.Stats.QuadDrawn++;
	}

	void Renderer2D::DrawSprite(TransformComponent& transform, SpriteRenderComponent& sprite) {
		if (!sprite.texture)
			DrawQuad(transform, sprite.color);
		else
			DrawQuad(transform, sprite.texture, sprite.color);
	}

	void Renderer2D::DrawGrid() {
		DrawQuad({ 0,0 }, {100,100}, { 1,1,1,1 });
		NextBatch();
	}



	void Renderer2D::ResetStats() {
		memset(&s_Data.Stats, 0, sizeof(Statistics));
	}

	

	Renderer2D::Statistics Renderer2D::GetStats() {
		return s_Data.Stats;
	}

}