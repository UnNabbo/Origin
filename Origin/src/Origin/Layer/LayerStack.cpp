#include "OGpch.h"

#include "LayerStack.h"


namespace Origin {
	LayerStack::LayerStack(){
		m_LayerInsert = m_Layers.begin();
	}
	LayerStack::~LayerStack(){
		for (Layer* layer : m_Layers) {
			delete layer;
		}
	}

	void LayerStack::PushLayer(Layer* layer) {
		m_LayerInsert = m_Layers.emplace(m_LayerInsert, layer);
		layer->OnAttach();
	}
	void LayerStack::PushOverlay(Layer* overlay) {
		m_Layers.emplace_back(overlay);
		overlay->OnAttach();
	}

	void LayerStack::PopLayer(Layer* layer) {
		auto x = std::find(m_Layers.begin(), m_Layers.end(), layer);

		if (x != m_Layers.end()) {
			m_Layers.erase(x);
			m_LayerInsert--;
		}
		layer->OnDeattach();

	}
	void LayerStack::PopOverlay(Layer* overlay) {
		auto x = std::find(m_Layers.begin(), m_Layers.end(), overlay);

		if (x != m_Layers.end()) {
			m_Layers.erase(x);
		}
		overlay->OnDeattach();

	}


}