#include "gui.h"
#include "../../ext/ImGui DirectX 11 Kiero Hook/imgui/imgui.h"
#include "../patching/Patches.h"

bool infinite_ammo = false;
bool no_grenade_delay = false;

void GUI::Render()
{
	ImGui::Begin("InxMenu for Crab Champions");

	/*if (ImGui::Checkbox("Infinite Ammo", &infinite_ammo)) {
		Patcher::TogglePatch(m_scanner, Patches::m_infinite_ammo_patch);
	}*/

	if (ImGui::BeginTabBar("##main")) {
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