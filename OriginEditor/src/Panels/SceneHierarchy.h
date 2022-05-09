#pragma once

#include "Origin/Core/Core.h"
#include "Origin/Scene/Scene.h"
#include "Origin/Scene/Entity.h"

namespace Origin {
	namespace Panels {
		class ORIGIN_API SceneHierarchy {
		public:
			SceneHierarchy() = default;
			SceneHierarchy(const Reference<Scene>& scene) : m_Context(scene) {}

			void SetContext(const Reference<Scene>& scene);

			void OnImGuiRender();

		private:
			void DrawNode(Entity entity);
			void DrawComponents(Entity entity);

		private:
			Reference<Scene> m_Context;
			Entity m_SelectedEntity;
		};
	}
}