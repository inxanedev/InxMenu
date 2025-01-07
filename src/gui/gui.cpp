#include "gui.h"
#include "../../ext/ImGui DirectX 11 Kiero Hook/imgui/imgui.h"
#include "../patching/Patches.h"
#include "../offsets/Offsets.h"

bool infinite_ammo = false;
bool no_grenade_delay = false;
bool god_mode = false;

float
base_speed,
base_dash_cooldown,
dash_speed,
dash_height,
melee_range,
melee_damage,
melee_knockback_strength;

void GUI::InitializeOffsets()
{
	god_mode = Offsets::m_god_mode->m_original;
	base_speed = Offsets::m_base_speed->m_original;
	base_dash_cooldown = Offsets::m_base_dash_cooldown->m_original;
	dash_speed = Offsets::m_dash_speed->m_original;
	dash_height = Offsets::m_dash_height->m_original;
	melee_range = Offsets::m_melee_range->m_original;
	melee_damage = Offsets::m_melee_damage->m_original;
	melee_knockback_strength = Offsets::m_melee_knockback_strength->m_original;
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
			if (ImGui::InputFloat("Base Speed", &base_speed, 0.0f, 1000.0f)) {
				Offsets::m_base_speed->SetValue(base_speed);
			}
			if (ImGui::InputFloat("Base Dash Cooldown", &base_dash_cooldown)) {
				Offsets::m_base_dash_cooldown->SetValue(base_dash_cooldown);
			}
			if (ImGui::InputFloat("Dash Speed", &dash_speed)) {
				Offsets::m_dash_speed->SetValue(dash_speed);
			}
			if (ImGui::InputFloat("Dash Height", &dash_height)) {
				Offsets::m_dash_height->SetValue(dash_height);
			}
			if (ImGui::InputFloat("Melee Range", &melee_range)) {
				Offsets::m_melee_range->SetValue(melee_range);
			}
			if (ImGui::InputFloat("Melee Damage", &melee_damage)) {
				Offsets::m_melee_damage->SetValue(melee_damage);
			}
			if (ImGui::InputFloat("Melee Knockback Strength", &melee_knockback_strength)) {
				Offsets::m_melee_knockback_strength->SetValue(melee_knockback_strength);
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

