#pragma once

#include "Origin/Core/Core.h"

#include "RendererAPI.h"

namespace Origin {
	class ORIGIN_API RenderCommand {
	public:


		inline static void Init() {
			s_RendererAPI->Init();
		}

		inline static void SetWireFrameView(bool state) {
			s_RendererAPI->SetWireFrameView(state);
		}

		inline static void ResizeWindow(uint32_t width, uint32_t height) {
			s_RendererAPI->ResizeWindow(width, height);
		}

		inline static void SetClearColor(const glm::vec4& color) {
			s_RendererAPI->SetClearColor(color);
		}

		inline static void Clear() {
			s_RendererAPI->Clear();
		}

		inline static void DrawIndexed(const Reference<VertexArray>& vertexArray, const uint32_t count = 0) {
			s_RendererAPI->DrawIndexed(vertexArray, count);
		}
	private:
		static RendererAPI* s_RendererAPI;
	};
}