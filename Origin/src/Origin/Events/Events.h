#pragma once
#include "Origin\Core.h"

#include <functional>

#include <sstream>

namespace Origin {

#define EVENT_CLASS_TYPE(type) inline static EventType GetStaticType() { return EventType::##type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }


#define EVENT_CLASS_CATEGORY(categoryFlags) virtual int GetCategoryFlags() const override { return categoryFlags; }


	enum class EventType {
		None = 0,
		WindowClose, WindowLostFocus, WindowFocus, WindowMoved, WindowResize,
		KeyPressed, KeyReleased,
		MouseButtonPressed, MouseButtonReleased, MouseScrolled, MouseMoved,
	};

	enum EventCategory {
		None = 0,
		EventCategoryApplication = BIT(0),
		EventCategoryInput = BIT(1),
		EventCategoryKeyboard = BIT(2),
		EventCategoryMouse = BIT(3),
		EventCategoryMouseButton = BIT(4)
	};

	class ORIGIN_API Event {
		friend class EventsDispatcher;
	public:
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;

		inline bool IsInCategory(EventCategory category) {
			return GetCategoryFlags() & category;
		}

	protected:
		bool m_handled = false;
	};

	class ORIGIN_API EventsDispatcher {
		template<typename T>
		using EventFn = std::function<bool(T&)>;
	public:
		EventsDispatcher(Event& event) : m_Event(event) {}

		template<typename T>
		bool Dispatch(EventFn<T> func) {
			if (m_Event.GetEventType() == T::GetStaticType()) {
				m_Event.m_handled = func(*(T*) & m_Event);
				return true;
			}
			return false;
		}
	private:
		Event& m_Event;
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e) {
		return os;
	}


}