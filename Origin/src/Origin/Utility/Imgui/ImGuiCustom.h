#pragma once

#include <ImGui/imgui.h>
#include <imgui/imgui_internal.h>

namespace ImGui {
	bool ColorEdit4(const char* label, ImVec2 size, float col[4], ImGuiColorEditFlags flags);
}
