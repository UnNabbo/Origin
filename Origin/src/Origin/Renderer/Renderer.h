#pragma once

#include "Origin/Core.h"

#include "RenderCommand.h"

#include "Utility/Camera.h"

#include "Primitives/Shader.h"


namespace Origin {

	class ORIGIN_API Renderer {
	public:
		static void BeginScene(Camera& camera);
		static void EndScene();

		static void Submit(std::shared_ptr<VertexArray>& vertexArray, std::shared_ptr<Shader>& shader);

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	private:
		struct SceneData {
			glm::mat4 ViewProjectionMatrix;
		};

		static SceneData* m_SceneData;
	};
}
