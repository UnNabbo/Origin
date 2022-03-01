#pragma once

#include "Origin/Core/Core.h"

namespace Origin {

	class ORIGIN_API Time {
	public:

		static void Update();
		static float GetSeconds() { return m_DeltaTime; }
		static float GetMilliseconds() { return m_DeltaTime * 1000; }

		operator float() const { return m_DeltaTime; }
	private:
		inline static float m_DeltaTime = 0;
		inline static float m_CurrentTime = 0;

	};

}

