#include "Origin.h"


class Sandbox : public Origin::Application {
public:

	void OnStart(){
		Origin::KeyPressedEvent a(100, 1);
	}

	void OnUpdate() {
	}
};



Origin::Application* CreateApplication() {
	return new Sandbox;
}