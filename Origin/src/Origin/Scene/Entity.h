#pragma once

#include "Origin/Core/Core.h"
#include "entt.hpp"


#include "Scene.h"

namespace Origin {
	class Entity {
	public:
		Entity() = default;
		Entity(entt::entity id, Scene* scene);
		~Entity() = default;

		template<typename Type, typename... Args>
		Type& AddComponent(Args&&... args) {
			return m_Scene->m_Registry.emplace<Type>(m_ID, args...);
		}

		template<typename Type>
		bool RemoveComponent() {
			return m_Scene->m_Registry.remove<Type>(m_ID);
		}

		template<typename Type>
		Type& GetComponent() {
			return m_Scene->m_Registry.get<Type>(m_ID);
		}

		template<typename... Type>
		bool HasComponents() {
			return m_Scene->m_Registry.all_of<Type...>(m_ID);
		}

		operator entt::entity() const { return m_ID; }
		operator bool() const { return m_ID != entt::null; }

		operator uint32_t() const { return (uint32_t)m_ID; }

		bool operator ==(Entity& other) const { return m_ID == other.m_ID; }
	private:
		entt::entity m_ID{ entt::null };
		Scene* m_Scene;
	};
}