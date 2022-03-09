#pragma once


#ifdef OG_PLATFORM_WINDOWS

extern Origin::Application* CreateApplication();

void main() {

	Origin::Log::Init();

	auto app = CreateApplication();
	app->Run();
	delete app;
}

#else
	#error Origin only support Windows! For more info read the github page: https://github.com/UnNabbo/Origin 
#endif