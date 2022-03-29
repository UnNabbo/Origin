#pragma once

#include "Origin/Core/Core.h"
#include "KeyCodes.h"
#include "MouseCodes.h"

namespace Origin{
	class ORIGIN_API Input {
	public:
		static void LockCursor(bool state);
		static bool IsKeyPressed(int keycode);
		static bool IsMouseButtonPressed(int button);
		static std::pair<float, float> GetMousePos();
	};
}