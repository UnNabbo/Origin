#pragma once

#include "Origin/Core.h"

#include "Origin/Events/Events.h"

namespace Origin {
	class ORIGIN_API Layer {
	public:
		Layer(const char *name = "Layer");
		virtual ~Layer();

		virtual void OnAttach();
		virtual void OnDeattach();
		virtual void OnUpdate() = 0;
		virtual void OnEvent(Event& e) = 0;

		inline void setName(const char* name) { m_name = name; }
	protected:
		const char* m_name;
	};

}