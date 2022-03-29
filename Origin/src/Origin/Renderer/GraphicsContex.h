#pragma once

#include "Origin/Core/Core.h"

namespace Origin {
	class ORIGIN_API GraphicsContext {
	public:
		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;
	};
}