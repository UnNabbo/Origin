#pragma once

#include "Origin/Core/Core.h"

#include "Primitives/VertexArray.h"

#include "glm/glm.hpp"

namespace Origin {

	
	class ORIGIN_API RendererAPI {
	public:
		enum class API {
			None = 0, OpenGL = 1
		};

	public:
		virtual void Init() = 0;

		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void Clear() = 0;
		virtual void ResizeWindow(uint32_t width, uint32_t height) = 0;
		virtual void SetWireFrameView(bool state) = 0;

		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray, const uint32_t count = 0) = 0;

		inline static API GetAPI() { return s_RendererAPI; }
	private:
		static API s_RendererAPI;
	};
}
