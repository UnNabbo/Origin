#pragma 
#include "Origin/Core.h"
#include <stdint.h>
#include <functional>

#include "Events\Events.h"

namespace Origin {

	struct ORIGIN_API WindowStruct {
		const char*  Title;
		uint32_t Width, Height;

		WindowStruct(const char* title = "Origin Engine", uint32_t width = 1280, uint32_t height = 720)
			: Title(title), Width(width), Height(height){
		}
	};

	class ORIGIN_API Window {
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual void onUpdate() = 0;

		virtual uint32_t GetHeight() const = 0;		
		virtual uint32_t GetWidth() const = 0;
		
		virtual void setEventCallback(const EventCallbackFn& callback) = 0;
		virtual void setVsync(bool state) = 0;
		virtual bool isVsync() const = 0;

		virtual void* GetNativeWindow() const = 0;

		static Window* Create(const WindowStruct& info = WindowStruct());
	};

}