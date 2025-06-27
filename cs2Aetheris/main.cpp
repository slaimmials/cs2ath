#include "menu/includes.h"
#include "menu/imgui_hook.h"
#include "menu/MenuSettings.h"
#include "lua/lua.hpp"
#include "TextEditor/TextEditor.h"
#include "api.h"

static TextEditor editor;
bool editorInitialized = false;

void ImGuiHook::Render() {
	if (!editorInitialized) {
		editorInitialized = true;
		editor.SetLanguageDefinition(TextEditor::LanguageDefinition::Lua());
		editor.SetText("");
	}

	ImGui::SetNextWindowSize(ImVec2(400, 300));
	ImGui::Begin("Aetheris", &settings::enabled, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize);
	
	ImVec2 title_pos = ImGui::GetWindowPos();
	float radius = 5.0f;
	float y_center = title_pos.y + ImGui::CalcTextSize("Aetheris").y * 0.5f + 3.5f;
	float x_offset = ImGui::CalcTextSize("Aetheris").x + 12.f;
	ImGui::GetOverlayDrawList()->AddCircleFilled(
		ImVec2(title_pos.x + x_offset, y_center),
		radius,
		settings::injected ? IM_COL32(0, 255, 0, 255) : IM_COL32(255, 0, 0, 255),
		30
	);

	ImVec2 content_min = ImGui::GetWindowContentRegionMin();
	ImVec2 content_max = ImGui::GetWindowContentRegionMax();
	ImVec2 content_size = ImVec2(content_max.x - content_min.x, content_max.y - content_min.y);
	float btnHeight = ImGui::GetFrameHeight();
	float spacing = ImGui::GetStyle().ItemSpacing.y;
	settings::codePanelSize = ImVec2(content_size.x, content_size.y - btnHeight);
	editor.Render("LuaScriptEditor", settings::codePanelSize);

	if (ImGui::Button("Execute")) {
		if (ImGui::Button("Execute")) {
			std::string code = editor.GetText();
			Lua::Execute(code.c_str());
		}
	}

	ImGui::End();
}

void ImGuiHook::MainThread() {
	MessageBoxA(NULL, "MainThread initialized", "Aetheris", MB_OK | MB_ICONINFORMATION);
	lua_State* L = luaL_newstate();
	luaL_openlibs(L);
	Lua::L = L;
	while (true) {

		Sleep(2);
	}
}

BOOL WINAPI DllMain(HMODULE hMod, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		ImGuiHook::Init(hMod);
		break;
	case DLL_PROCESS_DETACH:
		ImGuiHook::Shutdown();
		break;
	}
	return TRUE;
}