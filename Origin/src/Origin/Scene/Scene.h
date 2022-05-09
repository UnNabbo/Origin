#pragma once

#include "Origin/Core/Core.h"
#include "entt.hpp"
#include "Components.h"
#include "Origin/Events/Events.h"
#include "Origin/Renderer/Utility/Camera/EditorCamera.h"

namespace Origin {
	class Entity;

	class Scene {
	public:
		Scene();
		~Scene();

		Entity CreateEntity(std::string tag = "Entity");
		void DeleteEntity(Entity entity);


		void OnEvent(Event& e);
		void OnEditorUpdate(EditorCamera& camera);
		void OnRuntimeUpdate();

		inline Reference<Entity> GetMainCamera() { return m_MainCamera; }

		inline const entt::registry& GetRegistry() { return m_Registry; }
		inline const glm::vec2& GetViewportSize() { return m_ViewPortSize; }


		void ResizeCameras(float x, float y);
	private:
		glm::vec2 m_ViewPortSize;
		entt::registry m_Registry;
		Reference<Entity> m_MainCamera;
		friend class Entity;
		
	};

}