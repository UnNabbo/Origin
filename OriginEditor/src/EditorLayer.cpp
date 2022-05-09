#include "EditorLayer.h"

#include "ImGui/imgui.h"
#include "ImGui/imgui_internal.h"


#include "Origin/Core/ResourceManager/AssetPool.h"



namespace Origin {
	static int n = 1;
	static int k = 1;

		void EditorLayer::OnAttach() {
			scene = MakeReference<Scene>();

			FrameBufferFormat format = {
				{AttachmentType::Color, "Dio"},
				{AttachmentType::Depth, "Cane"},
			};
			EditorFrameBuffer = FrameBuffer::Create({ 1280, 720, format });
			RuntimeFrameBuffer = FrameBuffer::Create({ 1280, 720, format });


			texture = Texture2D::Create("E:/DEV/Origin/Origin/asset/images/bird.png");


			{
				Entity e = scene->CreateEntity("Main Camera");
				auto& transform = e.GetComponent<TransformComponent>();
				transform.Position = { 0, 0, -10};
				auto& camera = e.AddComponent<CameraComponent>(1280, 720);
				camera.Main = true;
			}
			


			SceneHierarchy.SetContext(scene);
		}

		void EditorLayer::OnUpdate() {
			if(m_IsViewPortHoverd)
				camera.OnUpdate();

	
			EditorFrameBuffer->Bind();

			RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
			RenderCommand::Clear();

			scene->OnEditorUpdate(camera);

			EditorFrameBuffer->Unbind();
			if (m_IsViewPortHoverd)
				camera.OnUpdate();


			RuntimeFrameBuffer->Bind();

			scene->OnRuntimeUpdate();

			RuntimeFrameBuffer->Unbind();
		}


		void EditorLayer::OnImGuiRender() {
			

			static bool dockspaceOpen = true;
			static bool opt_fullscreen_persistant = true;
			bool opt_fullscreen = opt_fullscreen_persistant;
			static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

			// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
			// because it would be confusing to have two docking targets within each others.
			ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
			if (opt_fullscreen) {
				ImGuiViewport* viewport = ImGui::GetMainViewport();
				ImGui::SetNextWindowPos(viewport->Pos);
				ImGui::SetNextWindowSize(viewport->Size);
				ImGui::SetNextWindowViewport(viewport->ID);
				ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
				ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
				window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
				window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
			}

			// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background and handle the pass-thru hole, so we ask Begin() to not render a background.
			if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
				window_flags |= ImGuiWindowFlags_NoBackground;

			// Important: note that we proceed even if Begin() returns false (aka window is collapsed).
			// This is because we want to keep our DockSpace() active. If a DockSpace() is inactive, 
			// all active windows docked into it will lose their parent and become undocked.
			// We cannot preserve the docking relationship between an active window and an inactive docking, otherwise 
			// any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
			ImGui::Begin("DockSpace", &dockspaceOpen, window_flags);
			ImGui::PopStyleVar();

			if (opt_fullscreen)
				ImGui::PopStyleVar(2);

			// DockSpace
			ImGuiIO& io = ImGui::GetIO();
			if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable) {
				ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
				ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
			}

			if (ImGui::BeginMenuBar()) {
				if (ImGui::BeginMenu("File")) {
					// Disabling fullscreen would allow the window to be moved to the front of other windows, 
					// which we can't undo at the moment without finer window depth/z control.
					//ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen_persistant);

				
					ImGui::EndMenu();
				}

				ImGui::EndMenuBar();
			}


			ImGui::Begin("Settings");

			auto stats = Renderer2D::GetStats();

			ImGui::Text("Renderer2D Stats: \n");
			ImGui::Text("DrawCall: %i\nQuad Drawn: %i\nTexture Used: %i", stats.DrawCalls, stats.QuadDrawn, stats.TextureUsed);


			static bool check = 1;
			static bool check1 = 0;
			static bool check2 = 0;

			ImGui::Checkbox("Camera Mode", &check);
			ImGui::Checkbox("WireFrame View", &check1);
			check2 = ImGui::Button("Reload Shaders", ImVec2(128, 32));

			RenderCommand::SetWireFrameView(check1);
	
			if (check2) {
				for (auto& shader : ShaderAssetPool::RetriveIterator()) {
					shader.second->Reload();
				}
				Renderer2D::ReloadSamplers();
			}
			ImGui::End();

			static int corner = 3;
			ImGuiWindowFlags window_flags1 = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav;
			if (corner != -1) {
				const float PAD = 10.0f;
				const ImGuiViewport* viewport = ImGui::GetMainViewport();
				ImVec2 work_pos = viewport->WorkPos; // Use work area to avoid menu-bar/task-bar, if any!
				ImVec2 work_size = viewport->WorkSize;
				ImVec2 window_pos, window_pos_pivot;
				window_pos.x = (corner & 1) ? (work_pos.x + work_size.x - PAD) : (work_pos.x + PAD);
				window_pos.y = (corner & 2) ? (work_pos.y + work_size.y - PAD) : (work_pos.y + PAD);
				window_pos_pivot.x = (corner & 1) ? 1.0f : 0.0f;
				window_pos_pivot.y = (corner & 2) ? 1.0f : 0.0f;
				ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always, window_pos_pivot);
				ImGui::SetNextWindowViewport(viewport->ID);
				window_flags1 |= ImGuiWindowFlags_NoMove;
			}
			ImGui::SetNextWindowBgAlpha(0.35f); // Transparent background
			if (ImGui::Begin("FPS", &dockspaceOpen, window_flags1)) {
				ImGui::Text("FPS: %f\nMS:  %f", 1 / Time::GetSeconds(), Time::GetMilliseconds());
				if (ImGui::BeginPopupContextWindow()) {
					if (ImGui::MenuItem("Custom", NULL, corner == -1)) corner = -1;
					if (ImGui::MenuItem("Top-left", NULL, corner == 0)) corner = 0;
					if (ImGui::MenuItem("Top-right", NULL, corner == 1)) corner = 1;
					if (ImGui::MenuItem("Bottom-left", NULL, corner == 2)) corner = 2;
					if (ImGui::MenuItem("Bottom-right", NULL, corner == 3)) corner = 3;
					if (&dockspaceOpen && ImGui::MenuItem("Close")) dockspaceOpen = false;
					ImGui::EndPopup();
				}
			}
			ImGui::End();

			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
			ImGuiWindowClass window_class;
			//window_class.DockNodeFlagsOverrideSet = ImGuiDockNodeFlags_NoTabBar;
			ImGui::SetNextWindowClass(&window_class);
			ImGui::Begin("Editor");

			static bool CameraMode = 0;
			if (ImGui::Button("2D", ImVec2{ 25,25 })) {
				if (CameraMode) {
					CameraMode = false;
				} else {
					CameraMode = true;
				}
				camera.setOrthographic(CameraMode);
			}
			m_IsViewPortHoverd = ImGui::IsWindowHovered();
			m_IsViewPortFocused = ImGui::IsWindowFocused();
			Application::Get().GetImGuiLayer()->SetBlockEvents(m_IsViewPortHoverd || m_IsViewPortFocused);
			ImVec2 viewPortPanelSize = ImGui::GetContentRegionAvail();
			if (m_ViewPortSize != *(glm::vec2*)&viewPortPanelSize) {
				EditorFrameBuffer->Resize(viewPortPanelSize.x, viewPortPanelSize.y);
				camera.SetViewportSize(viewPortPanelSize.x, viewPortPanelSize.y);
				m_ViewPortSize = { viewPortPanelSize.x, viewPortPanelSize.y };
			}

			uint32_t id = EditorFrameBuffer->GetAttachments()[0].AttachmentID;
			ImGui::Image((void*)id, ImVec2{ m_ViewPortSize.x, m_ViewPortSize.y }, ImVec2{ 0,1 }, ImVec2{ 1,0 });

			ImGui::End();

			ImGui::Begin("Game");
			ImVec2 RunTimeViewPortPanelSize = ImGui::GetContentRegionAvail();
			if (m_RuntimeViewPortSize != *(glm::vec2*)&RunTimeViewPortPanelSize) {
				RuntimeFrameBuffer->Resize(RunTimeViewPortPanelSize.x, RunTimeViewPortPanelSize.y);
				scene->ResizeCameras(RunTimeViewPortPanelSize.x, RunTimeViewPortPanelSize.y);
				m_RuntimeViewPortSize = { RunTimeViewPortPanelSize.x, RunTimeViewPortPanelSize.y };
			}

			uint32_t RuntimeID = RuntimeFrameBuffer->GetAttachments()[0].AttachmentID;
			ImGui::Image((void*)RuntimeID, ImVec2{ m_RuntimeViewPortSize.x, m_RuntimeViewPortSize.y }, ImVec2{ 0,1 }, ImVec2{ 1,0 });

			ImGui::End();
			ImGui::PopStyleVar();

			SceneHierarchy.OnImGuiRender();

			ImGui::End();

			
		}

		void EditorLayer::OnEvent(Event& e) {
			if (m_IsViewPortHoverd) {
				camera.OnEvent(e);
			}
			
		}



}