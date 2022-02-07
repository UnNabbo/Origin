#pragma once

#include "Origin/Core.h"
#include "KeyCodes.h"
#include "MouseCodes.h"

namespace Origin{
	class ORIGIN_API Input {
	public:
		static inline bool IsKeyPressed(int keycode){ return m_Instace->IsKeyPressedImpl(keycode); }
		static inline bool IsMouseButtonPressed(int button) { return m_Instace->IsMouseButtonPressedImpl(button); }
		static inline std::pair<float, float> GetMousePos() { return m_Instace->GetMousePosImpl(); }

	protected:
		virtual bool IsKeyPressedImpl(int keycode) = 0;
		virtual bool IsMouseButtonPressedImpl(int button) = 0;
		virtual std::pair<float, float> GetMousePosImpl() = 0;

	private:
		static Input* m_Instace;
	};
}