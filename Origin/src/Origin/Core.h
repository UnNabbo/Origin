#pragma once

#ifdef ORIGIN_PLATFORM_WINDOWS
	#ifdef ORIGIN_BUILD_DLL
		#define ORIGIN_API __declspec(dllexport)
	#else
		#define ORIGIN_API __declspec(dllimport)
	#endif
#else
	#error Origin only support Windows! For more info read the github page: https://github.com/UnNabbo/Origin 
#endif