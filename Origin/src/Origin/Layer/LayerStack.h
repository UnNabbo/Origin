#pragma once

#include "Origin/Core.h"

#include "Layer.h"

#include <vector>
#include <iterator>

namespace Origin {
	class ORIGIN_API LayerStack {
	public:
		LayerStack();
		~LayerStack();

		void PushLayer(Layer *layer);
		void PushOverlay(Layer* layer);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* layer);


		std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
		std::vector<Layer*>::iterator end() { return m_Layers.end(); }
	protected:
		std::vector<Layer*>m_Layers;
		uint32_t m_LayerInsertIndex = 0;
	};

}