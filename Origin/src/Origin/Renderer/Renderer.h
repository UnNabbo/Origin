#pragma once

#include "Origin/Core/Core.h"

#include "RenderCommand.h"

#include "Utility/Camera/Camera.h"

#include "Primitives/Shader.h"


namespace Origin {

	class ORIGIN_API Renderer {
	public:

		static void Init();
		static void BeginScene(Camera& camera);
		static void EndScene();

		static void ResizeWindow(uint32_t width, uint32_t height);
		static void Submit(Reference<VertexArray>& vertexArray, Reference<Shader>& shader, glm::mat4& model = glm::mat4(1));

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	private:
		struct SceneData {
			glm::mat4 ViewProjectionMatrix;
		};

		static SceneData* m_SceneData;
	};
}
