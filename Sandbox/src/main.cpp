#include "Origin.h"

#include <stdio.h>

class Sandbox : public Origin::Application {
public:

	void OnStart(){
		printf("Start\n");
	}

	void OnUpdate() {
		printf("Update\n");
	}
};



Origin::Application* CreateApplication() {
	return new Sandbox;
}