#pragma once

#include "Origin/Core/Core.h"

#include "RenderCommand.h"

#include "Utility/Camera/Camera.h"

#include "Primitives/Shader.h"

#include "Primitives/Texture.h"


namespace Origin {
	class ORIGIN_API Renderer2D{
	public:
		static void Init();
		static void Shutdown();
		
		static void BeginScene(Camera& camera);

		static void StartBatch();
		static void Flush();
		static void FlushAndReset();

		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Reference<Texture2D>& texture);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Reference<Texture2D>& texture);
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color, const Reference<Texture2D>& texture);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color, const Reference<Texture2D>& texture);

		static void DrawRotatedQuad(const glm::vec2& position, const glm::vec3& rotation, const glm::vec2& size, const glm::vec4& color);
		static void DrawRotatedQuad(const glm::vec3& position, const glm::vec3& rotation, const glm::vec2& size, const glm::vec4& color);
		static void DrawRotatedQuad(const glm::vec2& position, const glm::vec3& rotation, const glm::vec2& size, const Reference<Texture2D>& texture);
		static void DrawRotatedQuad(const glm::vec3& position, const glm::vec3& rotation, const glm::vec2& size, const Reference<Texture2D>& texture);
		static void DrawRotatedQuad(const glm::vec2& position, const glm::vec3& rotation, const glm::vec2& size, const glm::vec4& color, const Reference<Texture2D>& texture);
		static void DrawRotatedQuad(const glm::vec3& position, const glm::vec3& rotation, const glm::vec2& size, const glm::vec4& color, const Reference<Texture2D>& texture);


		static void EndScene();
	};
} 