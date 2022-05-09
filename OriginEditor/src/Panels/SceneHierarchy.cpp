#include "OGpch.h"

#include "SceneHierarchy.h"
#include "Origin/Scene/Components.h"
#include "Origin/Input/Input.h"
#include "Origin/Core/Application.h"

#include <ImGui/imgui.h>
#include <imgui/imgui_internal.h>

#include "Origin/Utility/Imgui/ImGuiCustom.h"

#include <glm/gtc/type_ptr.hpp>
#include <cstring>
#include <typeindex>
#include <typeinfo>

namespace Origin {
	namespace Panels {
		void SceneHierarchy::SetContext(const Reference<Scene>& scene) {
			m_Context = scene;
		}

		void SceneHierarchy::OnImGuiRender() {
			ImGui::Begin("SceneHierarchy");


			if (ImGui::BeginPopupContextWindow("SceneHierarchy PopUp", 1)) {
				if (ImGui::MenuItem("Create Empty")) {
					auto& id = m_Context->CreateEntity();
					m_SelectedEntity = { id, m_Context.get() };
				}
				if (ImGui::MenuItem("Create Square")) {
					auto& id = m_Context->CreateEntity();
					id.AddComponent<SpriteRenderComponent>();
					m_SelectedEntity = { id, m_Context.get() };
				}
				ImGui::EndPopup();
			}

			auto& TagView = m_Context->GetRegistry().view<TagComponent>();

			for (auto& EntityID : TagView) {
				Entity entity = { EntityID, m_Context.get() };
				DrawNode(entity);
			}


			ImGui::End();

			ImGui::Begin("Properties");

			if (m_SelectedEntity) {
				DrawComponents(m_SelectedEntity);
			}

			ImGui::End();


		}
		void SceneHierarchy::DrawNode(Entity entity) {
			auto& tag = entity.GetComponent<TagComponent>().Tag;

			ImGuiTreeNodeFlags flags = ((m_SelectedEntity == entity) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow;
			bool opened = ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)entity, flags, tag.c_str());
			if (ImGui::IsItemClicked()) {
				m_SelectedEntity = entity;
			}
			bool entityDeleted = false;
			if (ImGui::BeginPopupContextItem()) {
				if (ImGui::MenuItem("Delete Entity"))
					entityDeleted = true;

				ImGui::EndPopup();
			}
			if (Input::IsKeyPressed(OG_KEY_DELETE) & m_SelectedEntity == entity) {
				entityDeleted = true;
			}

			if (opened) {
				ImGui::TreePop();
			}
			if (entityDeleted) {
				m_Context->DeleteEntity(entity);
				if (m_SelectedEntity == entity)
					m_SelectedEntity = {};
			}
		}

		template<typename Type, typename Function>
		static void DrawComponent(const std::string& label, Entity entity, Function UIFunc, bool removable = true) {
			const ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_AllowItemOverlap | ImGuiTreeNodeFlags_FramePadding;
			if (entity.HasComponents<Type>()) {
				auto& component = entity.GetComponent<Type>();

				ImVec2 contentRegionAvailable = ImGui::GetContentRegionAvail();

				ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 4, 4 });
				float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
				ImGui::Separator();
				bool open = ImGui::TreeNodeEx((void*)typeid(Type).hash_code(), treeNodeFlags, label.c_str());
				ImGui::PopStyleVar();

				bool removeComponent = false;

				if (removable) {
					ImGui::SameLine(contentRegionAvailable.x - lineHeight * 0.5f);
					if (ImGui::Button("+", ImVec2{ lineHeight, lineHeight })) {
						ImGui::OpenPopup("ComponentSettings");
					}


					if (ImGui::BeginPopup("ComponentSettings")) {

						if (ImGui::MenuItem("Remove component"))
							removeComponent = true;

						ImGui::EndPopup();
					}
				}

				if (open) {
					UIFunc(component);
					ImGui::TreePop();
				}

				if (removeComponent)
					entity.RemoveComponent<Type>();
			}
			ImGui::NewLine();

		}

		static void DrawSlider3(std::string label, glm::vec3& values, const float reset = 0.0f, float columnWidth = 100.0f) {
			ImGui::PushID(label.c_str());

			ImGui::Columns(2, 0,false);
			ImGui::SetColumnWidth(0, columnWidth);
			ImGui::Text(label.c_str());
			ImGui::NextColumn();

			const ImVec2 contentRegionAvailable = ImGui::GetContentRegionAvail();

			ImGui::PushMultiItemsWidths(3, contentRegionAvailable.x - 50);
			ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });

			float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
			ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.2f, 0.2f, 1.0f });
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
			if (ImGui::Button("X", buttonSize))
				values.x = reset;
			ImGui::PopStyleColor(3);

			ImGui::SameLine();
			ImGui::DragFloat("##X", &values.x, 0.1f, 0.0f, 0.0f, "%.2f");
			ImGui::PopItemWidth();
			ImGui::SameLine();

			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.3f, 0.8f, 0.3f, 1.0f });
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
			if (ImGui::Button("Y", buttonSize))
				values.y = reset;
			ImGui::PopStyleColor(3);

			ImGui::SameLine();
			ImGui::DragFloat("##Y", &values.y, 0.1f, 0.0f, 0.0f, "%.2f");
			ImGui::PopItemWidth();
			ImGui::SameLine();

			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.2f, 0.35f, 0.9f, 1.0f });
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
			if (ImGui::Button("Z", buttonSize))
				values.z = reset;
			ImGui::PopStyleColor(3);

			ImGui::SameLine();
			ImGui::DragFloat("##Z", &values.z, 0.1f, 0.0f, 0.0f, "%.2f");
			ImGui::PopItemWidth();

			ImGui::PopStyleVar();

			ImGui::Columns(1);

			ImGui::PopID();
		}

		void SceneHierarchy::DrawComponents(Entity entity) {
			if (entity.HasComponents<TagComponent>()) {
				auto& tag = entity.GetComponent<TagComponent>().Tag;
				char buffer[256];
				memset(buffer, 0, sizeof(buffer));
				strcpy(buffer, tag.c_str());

				if (ImGui::InputText("##Tag", buffer, sizeof(buffer))) {
					tag = std::string(buffer);
				}
			}

			ImGui::SameLine();

			float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;

			{
				const ImVec2 contentRegionAvailable = ImGui::GetContentRegionAvail();

				if (ImGui::Button("Add Component", ImVec2(contentRegionAvailable.x , lineHeight)))
					ImGui::OpenPopup("AddComponent");

				if (ImGui::BeginPopupContextWindow("AddComponent")) {
					if (ImGui::MenuItem("Sprite Renderer")) {
						if (!entity.HasComponents<SpriteRenderComponent>())
							entity.AddComponent<SpriteRenderComponent>();
					}
					if (ImGui::MenuItem("Camera")) {
						if (!entity.HasComponents<CameraComponent>())
							entity.AddComponent<CameraComponent>(m_Context->GetViewportSize().x, m_Context->GetViewportSize().y);
					}


					ImGui::EndPopup();
				}
			}


			DrawComponent<TransformComponent>("Transform", entity, [&](auto& component) {

				auto& position = component.Position;
				DrawSlider3("Position", position);

				auto& rotation = component.Rotation;
				DrawSlider3("Rotation", rotation);

				auto& scale = component.Scale;
				if(entity.HasComponents<CameraComponent>())
					DrawSlider3("Scale", scale, 1.f);
				else
					DrawSlider3("Scale", scale);

				}, false);

			DrawComponent<SpriteRenderComponent>("Sprite Renderer", entity, [](auto& component) {
				auto& color = component.color;
				const ImVec2 contentRegionAvailable = ImGui::GetContentRegionAvail();

				ImGui::Columns(2, 0, false);
				ImGui::SetColumnWidth(0, 100.0f);

				ImGui::Text("Sprite");
				ImGui::Text("Color");

				ImGui::NextColumn();
				ImGui::NewLine();

				float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
				ImGui::ColorEdit4("##Color", ImVec2{ contentRegionAvailable.x - (98.0f + lineHeight)  ,lineHeight }, glm::value_ptr(color), ImGuiColorEditFlags_NoInputs);
				ImGui::SameLine(0, 0);
				if (ImGui::Button("+", ImVec2{ lineHeight, lineHeight })) {
					
				}
				ImGui::Columns(1);

			});

			DrawComponent<CameraComponent>("Camera", entity, [](auto& component) {
				auto& camera = component.camera;

				const ImVec2 contentRegionAvailable = ImGui::GetContentRegionAvail();
				float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;


				ImGui::Columns(2, 0, false);
				ImGui::SetColumnWidth(0, 100.0f);

				ImGui::Text("Background");

				ImGui::NextColumn();

		
				ImGui::ColorEdit4("##Color", ImVec2{ contentRegionAvailable.x - (100.0f + lineHeight)  ,lineHeight }, glm::value_ptr(component.ClearColor), ImGuiColorEditFlags_NoInputs);
				ImGui::SameLine(0, 0);
				if (ImGui::Button("+", ImVec2{ lineHeight, lineHeight })) {

				}

				ImGui::Columns(1);

				ImGui::Columns(2, 0, false);
				ImGui::SetColumnWidth(0, 100.0f);

				ImGui::Text("Projection");

				ImGui::NextColumn();

				const char* projectionTypeStrings[] = { "Orthographic","Perspective" };
				const char* currentProjectionTypeString = projectionTypeStrings[(int)camera.GetProjectionType()];
				ImGui::PushItemWidth(contentRegionAvailable.x - 100.f);
				if (ImGui::BeginCombo("##Projection", currentProjectionTypeString)) {
					for (int i = 0; i < 2; i++) {
						bool isSelected = currentProjectionTypeString == projectionTypeStrings[i];
						if (ImGui::Selectable(projectionTypeStrings[i], isSelected)) {
							currentProjectionTypeString = projectionTypeStrings[i];
							camera.SetProjectionType((ProjectionType)i);
						}

						if (isSelected)
							ImGui::SetItemDefaultFocus();
					}

					ImGui::EndCombo();
				}
				ImGui::PopItemWidth();

				ImGui::Columns(1);


				if (camera.GetProjectionType() == ProjectionType::Perspective) {
					ImGui::Columns(2, 0, false);
					ImGui::SetColumnWidth(0, 100.0f);

					ImGui::Text("Field of View");

					ImGui::NextColumn();

					auto fov = camera.GetFov();
					ImGui::PushItemWidth(contentRegionAvailable.x - 100.f);
					ImGui::DragFloat("##FOV", &fov, 0.1f, 0.0f, 0.0f, "%.2f");
					if (fov != camera.GetFov()) {
						camera.SetFov(fov);
					}
					ImGui::PopItemWidth();

					ImGui::Columns(1);
				}

				if (camera.GetProjectionType() == ProjectionType::Orthographic) {
					ImGui::Columns(2, 0, false);
					ImGui::SetColumnWidth(0, 100.0f);

					ImGui::Text("Size");

					ImGui::NextColumn();

					auto size = camera.GetSize();
					ImGui::PushItemWidth(contentRegionAvailable.x - 100.f);
					ImGui::DragFloat("##SIZE", &size, 0.1f, 0.0f, 0.0f, "%.2f");
					if (size != camera.GetSize()) {
						camera.SetSize(size);
					}
					ImGui::PopItemWidth();

					ImGui::Columns(1);

				}

				ImGui::Columns(2, 0, false);
				ImGui::SetColumnWidth(0, 100.0f);

				ImGui::Text("Clipping Planes");

				ImGui::NextColumn();
				ImGui::Text("Near");
				ImGui::SameLine(0, 10);

				ImGui::PushItemWidth(contentRegionAvailable.x - 140.f);
				ImGui::DragFloat("##Near", &camera.GetClippingPlane().x, 0.1f, 0.0f, 0.0f, "%.2f");
				ImGui::PopItemWidth();
				ImGui::Text("Far ");

				ImGui::SameLine(0, 10);
				ImGui::PushItemWidth(contentRegionAvailable.x - 140.f);

				ImGui::DragFloat("##Far", &camera.GetClippingPlane().y, 0.1f, 0.0f, 0.0f, "%.2f");
				ImGui::PopItemWidth();

				ImGui::Columns(1);

				ImGui::Columns(2, 0, false);
				ImGui::SetColumnWidth(0, 100.0f);

				ImGui::Text("Main Camera");

				ImGui::NextColumn();

				ImGui::Checkbox("##Primary", &component.Main);

				ImGui::Columns(1);

				

				});

			

			
		}
	}
}

