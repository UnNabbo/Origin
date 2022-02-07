#include "Origin/Core.h"

#include "Origin/Layer/Layer.h"

#include "Origin/Events/InputEvents.h"

#include "Origin/Events/ApplicationEvents.h"

namespace Origin {
	class ORIGIN_API ImGuiLayer : public Layer {
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach() override;
		void OnUpdate() override;
		void OnEvent(Event& event) override;
		void OnDeattach() override;

	private:
		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
		bool OnMouseMovedEvent(MouseMovedEvent& e);
		bool OnMouseScrolledEvent(MouseScrolledEvent& e);
		bool OnKeyPressedEvent(KeyPressedEvent& e);
		bool OnKeyReleasedEvent(KeyReleasedEvent& e);
		bool OnWindowResizeEvent(WindowResizeEvent& e);
		bool OnKeyTypedEvent(KeyTypedEvent& e);

	};
}