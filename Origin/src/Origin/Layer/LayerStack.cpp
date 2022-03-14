#include "OGpch.h"

#include "LayerStack.h"


namespace Origin {
	LayerStack::LayerStack(){}

	LayerStack::~LayerStack(){
		for (Layer* layer : m_Layers) {
			delete layer;
		}
	}

	void LayerStack::PushLayer(Layer* layer) {
		m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex++, layer);
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
			m_LayerInsertIndex--;
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