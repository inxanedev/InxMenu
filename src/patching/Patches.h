#pragma once
#include <vector>
#include "Patch.h"
class Patches
{
public:
	static inline Patch m_infinite_ammo_patch{ "ff 8e ? ? ? ? 48 8b ce e8 ? ? ? ? ff 86", 0, [](safetyhook::Context& ctx) {
		(*((int*)(ctx.rsi + 0x2e8)))++;
	}};
};