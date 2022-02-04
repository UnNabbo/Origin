#pragma once

#include "Events.h"

#include <stdio.h>

namespace Origin {

	class ORIGIN_API WindowCloseEvent : public Event {
	public:
		WindowCloseEvent() {}

		EVENT_CLASS_TYPE(WindowClose)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)

	};

	class ORIGIN_API WindowLostFocusEvent : public Event {
	public:
		WindowLostFocusEvent() {}

		EVENT_CLASS_TYPE(WindowLostFocus);
		EVENT_CLASS_CATEGORY(EventCategoryApplication);

	};

	class ORIGIN_API WindowFocusEvent : public Event {
	public:
		WindowFocusEvent() {}

		EVENT_CLASS_TYPE(WindowFocus);
		EVENT_CLASS_CATEGORY(EventCategoryApplication);


	};

	class ORIGIN_API WindowMovedEvent : public Event {
	public:
		WindowMovedEvent(uint32_t xPos, uint32_t yPos)
			: m_xPos(xPos), m_yPos(yPos) {}

		EVENT_CLASS_TYPE(WindowMoved);
		EVENT_CLASS_CATEGORY(EventCategoryApplication);

	private:
		uint32_t m_xPos, m_yPos;
	};


	class ORIGIN_API WindowResizeEvent : public Event {
	public:
		WindowResizeEvent(uint32_t Width, uint32_t Height) 
			: m_Width(Width), m_Height(Height) {
}

		EVENT_CLASS_TYPE(WindowResize);
		EVENT_CLASS_CATEGORY(EventCategoryApplication);

	private:
		uint32_t m_Width, m_Height;
	};

}