#pragma once

#include "Origin/Core/Core.h"

#include "Origin/Layer/Layer.h"

namespace Origin {
	class ORIGIN_API ImGuiLayer : public Layer {
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDeattach() override;
		virtual void OnEvent(Event& e) override;
		void SetDarkThemeColors();

		inline void SetBlockEvents(bool state) { m_BlockEvents = state; }

		static void Begin();
		static void End();
	private:
		bool m_BlockEvents = true;
	};
}