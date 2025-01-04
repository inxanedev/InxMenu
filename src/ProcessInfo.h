#pragma once
#include <Windows.h>
#include <TlHelp32.h>
#include <tchar.h>
#include <cstdint>
class ProcessInfo
{
public:
	HANDLE m_handle;
	uintptr_t m_base_address;
	uint32_t m_memory_size;

	ProcessInfo();

	uintptr_t GetModuleBaseAddress(const wchar_t* module_name);
	HMODULE GetCurrentModule();

	int GetPID();
};

