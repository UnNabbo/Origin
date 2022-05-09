#include "OGpch.h"

#include "Scene.h"

#include "Components.h"
#include "Entity.h"
#include "Origin/Events/ApplicationEvents.h"
#include "Origin/Renderer/Renderer2D.h"


namespace Origin {
	Scene::Scene() {

	}

	Scene::~Scene() {
	}

	Entity Scene::CreateEntity(std::string tag) {
		Entity entity = { m_Registry.create(), this};
		entity.AddComponent<TagComponent>(tag);
		entity.AddComponent<TransformComponent>(glm::vec3(0,0,0),glm::vec3(0,0,0),glm::vec3(1,1,1));
		return entity;
	}

	void Scene::DeleteEntity(Entity entity) {
		m_Registry.destroy(entity);
	}

	void Scene::OnEvent(Event& e) {

	}

	void Scene::OnEditorUpdate(EditorCamera& camera) {
		Renderer2D::BeginScene(camera);
		auto& view = m_Registry.view<TransformComponent, SpriteRenderComponent>();
		for (auto& e : view){
			Renderer2D::DrawSprite(view.get<TransformComponent>(e), view.get<SpriteRenderComponent>(e));
		}
		Renderer2D::EndScene();

	}

	void Scene::OnRuntimeUpdate() {
		{
			auto& view = m_Registry.view<CameraComponent>();
			for (auto entity : view) {
				auto& camera = view.get<CameraComponent>(entity);

				if (camera.Main) {
					m_MainCamera = MakeScopedReference<Entity>(entity, this);
					m_ViewPortSize = camera.camera.GetViewPort();
					break;
				}
			}
		}
		

		if (m_Registry.valid(*m_MainCamera.get())) {
			if (m_MainCamera->HasComponents<CameraComponent>()) {
				RenderCommand::SetClearColor(m_MainCamera->GetComponent<CameraComponent>().ClearColor);
				RenderCommand::Clear();

				Renderer2D::BeginScene(*this);

				auto& view = m_Registry.view<TransformComponent, SpriteRenderComponent>();
				for (auto& e : view) {
					Renderer2D::DrawSprite(view.get<TransformComponent>(e), view.get<SpriteRenderComponent>(e));
				}
				Renderer2D::EndScene();
			}
		}

	}
	void Scene::ResizeCameras(float x, float y) {
		auto view = m_Registry.view<CameraComponent>();
		m_ViewPortSize = { x,y };
		for (auto entity : view) {
			auto& cameraComponent = view.get<CameraComponent>(entity);
			if (!cameraComponent.FixedViewPort)
				cameraComponent.camera.SetViewportSize({ x, y });
		}
	}
}