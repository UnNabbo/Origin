#include "OGpch.h"

#include "Platform.h"

namespace Origin {
#ifdef OG_PLATFORM_WINDOWS
	Platform::PlatformAPI Platform::s_PlatformAPI = Platform::PlatformAPI::Windows;
#endif

}