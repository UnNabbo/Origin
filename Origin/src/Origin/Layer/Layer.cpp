#include "OGpch.h"

#include "Layer.h"

namespace Origin {
	
	Layer::Layer(const char* name)
		:m_name(name){}

	Layer::~Layer(){}

	void Layer::OnAttach() {}

	void Layer::OnDeattach() {}

	void Layer::OnImGuiRender() {}

	void Layer::OnUpdate() {}

	void Layer::OnEvent(Event& e) {}

}