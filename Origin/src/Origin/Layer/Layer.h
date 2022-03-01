#pragma once

#include "Origin/Core/Core.h"

#include "Origin/Events/Events.h"

namespace Origin {
	class ORIGIN_API Layer {
	public:
		Layer(const char *name = "Layer");
		virtual ~Layer();

		virtual void OnAttach();
		virtual void OnDeattach();
		virtual void OnImGuiRender();
		virtual void OnUpdate();
		virtual void OnEvent(Event& e);

		inline void setName(const char* name) { m_name = name; }
	protected:
		const char* m_name;
	};

}