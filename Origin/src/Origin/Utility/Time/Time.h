#pragma once

#include "Origin/Core/Core.h"

namespace Origin {

	class ORIGIN_API Time {
	public:

		static void Update();
		static float GetTime();
		static float GetSeconds() { return m_DeltaTime; }
		static float GetMilliseconds() { return m_DeltaTime * 1000; }

	private:
		inline static float m_DeltaTime = 0;
		inline static float m_CurrentTime = 0;
		inline static float m_TimeFromStart = 0;
	
	};

}

