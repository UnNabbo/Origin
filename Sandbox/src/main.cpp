#include "Origin.h"

class Sandbox : public Origin::Application {
public:

	void OnStart(){
		ORIGIN_INFO("HELLO");
	}

	void OnUpdate() {
	}
};



Origin::Application* CreateApplication() {
	return new Sandbox;
}