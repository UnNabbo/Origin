#pragma once
#include "Origin\Events\Events.h"
#include <iostream>
#include <string>

namespace Origin {

	class ORIGIN_API KeyEvent : public Event {
	public:
		inline int GetKeyCode() { return m_keycode; }

		EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryKeyboard)
	protected:
		KeyEvent(int keycode)
			: m_keycode(keycode) {
		}

		int m_keycode;
	};

	class ORIGIN_API KeyPressedEvent : public KeyEvent {
		friend std::ostream& operator<<(std::ostream& os, KeyPressedEvent& e);
	public:
		KeyPressedEvent(int keycode, bool held)
			: KeyEvent(keycode), m_held(held){}

		inline bool IsHeld() { return m_held; }

		EVENT_CLASS_TYPE(KeyPressed)
	private:
		bool m_held;
	};

	std::ostream& operator<<(std::ostream& os, KeyPressedEvent& e) {
		os << e.GetKeyCode();
		return os;
	}

	class ORIGIN_API KeyReleasedEvent : public KeyEvent {
	public:
		KeyReleasedEvent(int keycode)
			: KeyEvent(keycode) {
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};

	class ORIGIN_API MouseButtonPressedEvent : public Event {
	public:
		MouseButtonPressedEvent(int keycode, bool held)
			: m_keycode(keycode), m_held(held){
			int x = 0;
		}

		inline int GetKeyCode() { return m_keycode; }

		EVENT_CLASS_TYPE(MouseButtonPressed)
		EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryMouse)
	private:
		int m_keycode;
		bool m_held;
	};


	class ORIGIN_API MouseButtonReleasedEvent : public Event {
	public:
		MouseButtonReleasedEvent(int keycode)
			: m_keycode(keycode) {}

		inline int GetKeyCode() { return m_keycode; }

		EVENT_CLASS_TYPE(MouseButtonReleased)
		EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryMouse)
	private:
		int m_keycode;
	};

	class ORIGIN_API MouseMovedEvent : public Event {
	public:
		MouseMovedEvent(float x, float y)
			: m_MouseX(x), m_MouseY(y) {}

		inline float GetX() { return m_MouseX; }
		inline float GetY() { return m_MouseY; }

		EVENT_CLASS_TYPE(MouseMoved)
		EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryMouse)
	private:
		float m_MouseX;
		float m_MouseY;
	};

	class ORIGIN_API MouseScrolledEvent : public Event {
	public:
		MouseScrolledEvent(float xOffset, float yOffset)
			: m_MouseXoffset(xOffset), m_MouseYoffset(yOffset) {}

		inline float GetXoffeset() { return m_MouseXoffset; }
		inline float GetYoffeset() { return m_MouseYoffset; }


		EVENT_CLASS_TYPE(MouseScrolled)
		EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryMouse)
	private:
		float m_MouseXoffset;
		float m_MouseYoffset;

	};



}