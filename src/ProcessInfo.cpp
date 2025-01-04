#include "ProcessInfo.h"
#include <Psapi.h>

ProcessInfo::ProcessInfo()
{
	m_handle = GetCurrentProcess();
	m_base_address = GetModuleBaseAddress(_T("CrabChampions-Win64-Shipping.exe"));

	MODULEINFO info;
	GetModuleInformation(m_handle, GetCurrentModule(), &info, sizeof(MODULEINFO));

	m_memory_size = info.SizeOfImage;
}

uintptr_t ProcessInfo::GetModuleBaseAddress(const wchar_t* module_name)
{
	uintptr_t base_address = 0;
	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, GetPID());
	MODULEENTRY32 entry = { 0 };
	entry.dwSize = sizeof(MODULEENTRY32);

	if (Module32First(snapshot, &entry)) {
		do {
			if (_tcscmp(entry.szModule, module_name) == 0) {
				base_address = (uintptr_t)entry.modBaseAddr;
				break;
			}
		} while (Module32Next(snapshot, &entry));
	}

	CloseHandle(snapshot);
	return base_address;
}

HMODULE ProcessInfo::GetCurrentModule()
{
	return GetModuleHandleA("CrabChampions-Win64-Shipping.exe");
}

int ProcessInfo::GetPID()
{
	return GetProcessId(m_handle);
}
