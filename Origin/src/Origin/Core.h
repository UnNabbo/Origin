#pragma once

#ifdef OG_PLATFORM_WINDOWS
	#ifdef OG_BUILD_DLL
		#define ORIGIN_API __declspec(dllexport)
	#else
		#define ORIGIN_API __declspec(dllimport)
	#endif
#else
	#error Origin only support Windows! For more info read the github page: https://github.com/UnNabbo/Origin 
#endif

#define BIT(x) (1 << x)