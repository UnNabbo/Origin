#include "Origin.h"


class Sandbox : public Origin::Application {
public:

	void OnStart(){
		
	}

	void OnUpdate() {
	}
};



Origin::Application* CreateApplication() {
	return new Sandbox;
}