#pragma once
#include "../ProcessInfo.h"
#include "Offset.h"
#include <unordered_map>
#include <any>
#include <stdexcept>

static uintptr_t pBase_GameManager = 0;

class Offsets {
public:

	inline static Offset<bool>* m_god_mode = nullptr;
	inline static Offset<float>* m_base_speed = nullptr;
	inline static Offset<float>* m_base_dash_cooldown = nullptr;
	inline static Offset<float>* m_dash_speed = nullptr;
	inline static Offset<float>* m_dash_height = nullptr;
	inline static Offset<float>* m_melee_range = nullptr;
	inline static Offset<float>* m_melee_damage = nullptr;
	inline static Offset<float>* m_melee_knockback_strength = nullptr;

	static void Initialize() {
		if (pBase_GameManager == 0) {
			throw std::runtime_error("pBase_GameManager is null");
		}
		m_god_mode = new Offset<bool>(pBase_GameManager, 0, {0xd28, 0x38, 0x0, 0x30, 0x2a0, 0x619});
		m_base_speed = new Offset<float>(pBase_GameManager, 0, { 0xd28, 0x38, 0x0, 0x30, 0x2a0, 0x5bc });
		m_base_dash_cooldown = new Offset<float>(pBase_GameManager, 0, { 0xd28, 0x38, 0x0, 0x30, 0x2a0, 0x89c });
		m_dash_speed = new Offset<float>(pBase_GameManager, 0, { 0xd28, 0x38, 0x0, 0x30, 0x2a0, 0x8c0 });
		m_dash_height = new Offset<float>(pBase_GameManager, 0, { 0xd28, 0x38, 0x0, 0x30, 0x2a0, 0x8c4 });
		m_melee_range = new Offset<float>(pBase_GameManager, 0, { 0xd28, 0x38, 0x0, 0x30, 0x2a0, 0x9a8 });
		m_melee_damage = new Offset<float>(pBase_GameManager, 0, { 0xd28, 0x38, 0x0, 0x30, 0x2a0, 0x9ac });
		m_melee_knockback_strength = new Offset<float>(pBase_GameManager, 0, { 0xd28, 0x38, 0x0, 0x30, 0x2a0, 0x9b0 });
		
	}
};