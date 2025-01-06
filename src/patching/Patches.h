#pragma once
#include <vector>
#include "Patch.h"
class Patches
{
public:
	static inline Patch m_infinite_ammo_patch{ "ff 8e ? ? ? ? 48 8b ce e8 ? ? ? ? ff 86", 0, [](safetyhook::Context& ctx) {
		(*((int*)(ctx.rsi + 0x2e8)))++;
	}};

	static inline Patch m_no_grenade_delay_patch{ "f3 0f 11 89 ? ? ? ? 48 81 c1 ? ? ? ? e8 ? ? ? ? f3 0f 10 83", 0, [](safetyhook::Context& ctx) {
		ctx.xmm1.f64[0] = 0.0f;
	}};
};