#pragma once

#include "Origin/Core/Core.h"

#include "RenderCommand.h"

#include "Utility/Camera/Camera.h"

#include "Primitives/Shader.h"

#include "Primitives/Texture.h"

#include "Origin/Scene/Scene.h"

#include "Origin/Scene/Components.h"

namespace Origin {
	class ORIGIN_API Renderer2D{
	public:
		static struct Statistics {
			uint32_t DrawCalls;
			uint32_t TextureUsed;
			uint32_t QuadDrawn;
		};

		static void Init();
		static void Shutdown();
		
		static void BeginScene(Scene& scene, bool showGrid = true);
		static void BeginScene(EditorCamera& scene);


		static Renderer2D::Statistics GetStats();
		static void ResetStats();

		//TODO REMOVE-----------------
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Reference<Texture2D>& texture, const glm::vec4& color = glm::vec4(1));
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Reference<Texture2D>& texture, const glm::vec4& color = glm::vec4(1));
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Reference<SubTexture2D>& texture, const glm::vec4& color = glm::vec4(1));
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Reference<SubTexture2D>& texture, const glm::vec4& color = glm::vec4(1));

		static void DrawRotatedQuad(const glm::vec2& position, const glm::vec3& rotation, const glm::vec2& size, const glm::vec4& color);
		static void DrawRotatedQuad(const glm::vec3& position, const glm::vec3& rotation, const glm::vec2& size, const glm::vec4& color);
		static void DrawRotatedQuad(const glm::vec2& position, const glm::vec3& rotation, const glm::vec2& size, const Reference<Texture2D>& texture, const glm::vec4& color = glm::vec4(1));
		static void DrawRotatedQuad(const glm::vec3& position, const glm::vec3& rotation, const glm::vec2& size, const Reference<Texture2D>& texture, const glm::vec4& color = glm::vec4(1));
		//----------------------------

		static void DrawQuad(glm::mat4 transform, const glm::vec4& color = glm::vec4(1));
		static void DrawQuad(glm::mat4 transform, const Reference<Texture2D>& texture, const glm::vec4& color = glm::vec4(1));

		static void DrawSprite(TransformComponent& transform, SpriteRenderComponent&);

		static void DrawGrid();

		static void ReloadSamplers();

		static void EndScene();

	private:
		static void StartBatch();
		static void Flush();
		static void NextBatch();
	};
} 