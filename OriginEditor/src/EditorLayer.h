#pragma once

#include "Origin.h"

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

		Reference<Texture2D> texture;
		Reference<TextureAtlas> textureAtlas;

		Reference<SubTexture2D> subtexture;
		Reference<SubTexture2D> subtexture1;
		Reference<SubTexture2D> subtexture2;

		Reference<FrameBuffer> frameBuffer;
		EditorCamera camera = EditorCamera(45.0f, 1280.0f / 720.0f, 0.001f, 1000.0f);

	};
}