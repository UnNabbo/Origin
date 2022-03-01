#pragma once

#include "Origin/Core/Core.h"

#include "Origin/Renderer/RendererAPI.h"

namespace Origin {
	class ORIGIN_API OpenGLRendererAPI : public RendererAPI {
		virtual void Init() override;

		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Clear() override;

		virtual void DrawIndexed(const AssetRef<VertexArray>& vertexArray) override;
	};
}
