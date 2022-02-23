#pragma once

#include "Origin/Core.h"

namespace Origin {

	enum class RendererAPI {
		None = 0, OpenGL = 1
	};
	class ORIGIN_API Renderer {
	public:
		inline static RendererAPI GetAPI() { return s_RendererAPI; }
	private:
		static RendererAPI s_RendererAPI;
	};
}
