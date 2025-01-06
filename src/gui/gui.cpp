#include "gui.h"
#include "../../ext/ImGui DirectX 11 Kiero Hook/imgui/imgui.h"
#include "../patching/Patches.h"
#include "../offsets/Offsets.h"

bool infinite_ammo = false;
bool no_grenade_delay = false;
bool god_mode = false;

void GUI::InitializeOffsets()
{
	god_mode = Offsets::m_god_mode->m_original;
}

void GUI::Render()
{
	ImGui::Begin("InxMenu for Crab Champions");

	/*if (ImGui::Checkbox("Infinite Ammo", &infinite_ammo)) {
		Patcher::TogglePatch(m_scanner, Patches::m_infinite_ammo_patch);
	}*/

	if (ImGui::BeginTabBar("##main")) {
		if (ImGui::BeginTabItem("Player")) {
			if (ImGui::Checkbox("God Mode", &god_mode)) {
				Offsets::m_god_mode->SetValue(god_mode);
			}
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Weapon")) {
			if (ImGui::Checkbox("Infinite Ammo", &infinite_ammo)) {
				Patches::m_infinite_ammo_patch.Toggle();
			}
			if (ImGui::Checkbox("No Grenade Delay", &no_grenade_delay)) {
				Patches::m_no_grenade_delay_patch.Toggle();
			}
			ImGui::EndTabItem();
		}
	}

	ImGui::End();
}

