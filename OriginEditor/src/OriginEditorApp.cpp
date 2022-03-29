#include <Origin.h>
#include <Origin/Core/EntryPoint.h>

#include "EditorLayer.h"

namespace Origin {
	class OriginEditor : public Application {
	public:

		OriginEditor() {
			PushLayer(new EditorLayer);
		}

		~OriginEditor() {

		}
	};
}

Origin::Application* CreateApplication() {
	return new Origin::OriginEditor;
}