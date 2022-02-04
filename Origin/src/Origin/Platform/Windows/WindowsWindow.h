#pragma once

#include "Origin\Window.h"

#include "GLFW\glfw3.h"

namespace Origin {
	class ORIGIN_API WindowsWindow : public Window {
	public:
		WindowsWindow(const WindowStruct& info);
		~WindowsWindow();

		void onUpdate();

		inline uint32_t getHeight() const override { return m_data.Height; }
		inline uint32_t getWidth() const override { return m_data.Width; }
		inline bool isVsync() const override { return m_data.Vsync; }
		inline void setEventCallback(const EventCallbackFn& callback) override { m_data.EventCallback = callback; };

		void setVsync(bool state);

		void Init(const WindowStruct& info);
		void Shutdown();

	private:
		GLFWwindow* m_Window;

		struct WindowData {
			const char* Title;
			uint32_t Width, Height;
			bool Vsync;

			EventCallbackFn EventCallback;
		};

		WindowData m_data;
	};


}