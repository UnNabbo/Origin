#pragma once

#include "Origin/Core.h"

#include "Origin/Input/Input.h"

namespace Origin {
	class ORIGIN_API WindowsInput : public Input{
	protected:
		virtual bool IsKeyPressedImpl(int keycode) override;
		virtual bool IsMouseButtonPressedImpl(int button) override;
		virtual std::pair<float, float> GetMousePosImpl() override;


	};

}