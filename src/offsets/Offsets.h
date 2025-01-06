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

	static void Initialize() {
		if (pBase_GameManager == 0) {
			throw std::runtime_error("pBase_GameManager is null");
		}
		m_god_mode = new Offset<bool>(pBase_GameManager, 0, {0xd28, 0x38, 0x0, 0x30, 0x2a0, 0x619});
	}
};