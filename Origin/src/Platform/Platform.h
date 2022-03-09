#pragma once

namespace Origin {

	class Platform {
	public:
		enum class PlatformAPI {
			None = 0,
			Windows = 1,
		};
		
		static PlatformAPI GetAPI() { return s_PlatformAPI; }

	private:
		static PlatformAPI s_PlatformAPI;
	};
}
