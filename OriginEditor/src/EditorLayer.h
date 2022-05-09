#pragma once

#include "Origin.h"
#include "Panels/SceneHierarchy.h"

namespace Origin {

	class EditorLayer : public Layer {
	public:
		EditorLayer() : Layer("Editor") {}

		virtual void OnAttach() override;

		virtual void OnUpdate() override;

		virtual void OnImGuiRender() override;

		virtual void OnEvent(Event& e) override;
	private:
		glm::vec2 m_ViewPortSize{0,0};
		glm::vec2 m_RuntimeViewPortSize{ 0,0 };

		Reference<Texture2D> texture;

		Reference<TextureAtlas> textureAtlas;

		Reference<Scene> scene;

		Reference<FrameBuffer> EditorFrameBuffer;
		Reference<FrameBuffer> RuntimeFrameBuffer;

		EditorCamera camera = EditorCamera(45.0f, (float)Application::Get().GetWindow().GetWidth() / Application::Get().GetWindow().GetHeight(), 0.001f, 10000.0f);
		bool m_IsViewPortHoverd = false;
		bool m_IsViewPortFocused = false;
		Panels::SceneHierarchy SceneHierarchy;
	};
}