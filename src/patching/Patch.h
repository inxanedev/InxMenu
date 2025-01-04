#pragma once
#include <string>
#include <vector>
#include <Windows.h>
#include "../../ext/safetyhook.hpp"
class Patch
{
public:
	Patch(const std::string& signature, int offset, safetyhook::MidHookFn function);
	bool Toggle();
private:
	safetyhook::MidHook m_hook;
	safetyhook::MidHookFn m_patch;
	uintptr_t m_address;
	bool m_on;
};