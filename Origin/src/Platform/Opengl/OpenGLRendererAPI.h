#pragma once

#include "Origin/Core/Core.h"

#include "Origin/Renderer/RendererAPI.h"

namespace Origin {
	class ORIGIN_API OpenGLRendererAPI : public RendererAPI {
		virtual void Init() override;

		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Clear() override;
		virtual void ResizeWindow(uint32_t width, uint32_t height) override;
		virtual void SetWireFrameView(bool state) override;

		virtual void DrawIndexed(const Reference<VertexArray>& vertexArray, const uint32_t count = 0) override;

	};
}
