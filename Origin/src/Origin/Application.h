#pragma once

#include "Core.h"

namespace Origin {
	class ORIGIN_API Application {
	public:
		Application();

		~Application();

		virtual void OnStart();

		virtual void OnUpdate();

		void Run();
	};
}

