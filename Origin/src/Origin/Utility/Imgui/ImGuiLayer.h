#pragma once

#include "Origin/Core.h"

#include "Origin/Layer/Layer.h"

namespace Origin {
	class ORIGIN_API ImGuiLayer : public Layer {
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDeattach() override;
		virtual void OnImGuiRender() override;

		static void Begin();
		static void End();

	};
}