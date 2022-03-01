#pragma once

#include "Origin/Core/Window.h"

#include "Origin/Renderer/GraphicsContex.h"

struct GLFWwindow;



namespace Origin {
	class ORIGIN_API WindowsWindow : public Window {
	public:
		WindowsWindow(const WindowStruct& info);
		~WindowsWindow();

		virtual void onUpdate();

		inline virtual uint32_t GetHeight() const override { return m_data.Height; }
		inline virtual uint32_t GetWidth() const override { return m_data.Width; }
		inline virtual void* GetNativeWindow() const override { return m_Window; }
		inline virtual bool isVsync() const override { return m_data.Vsync; }
		inline virtual void setEventCallback(const EventCallbackFn& callback) override { m_data.EventCallback = callback; };
		void virtual setVsync(bool state);

		virtual void Bind();

		void Init(const WindowStruct& info);
		void Shutdown();

	private:
		GLFWwindow* m_Window;
		GraphicsContext* m_context;

		struct WindowData {
			const char* Title;
			uint32_t Width, Height;
			bool Vsync;

			EventCallbackFn EventCallback;
		};

		WindowData m_data;
	};


}