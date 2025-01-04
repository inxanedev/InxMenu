#include "InxMenu.h"
#include "../ProcessInfo.h"
#include "../patching/PatternScanner.h"
#include "../patching/Patcher.h"
#include <iostream>

InxMenu::InxMenu()
{
	

	ProcessInfo process_info;

	std::cout << process_info.m_base_address << std::endl;
	std::cout << process_info.m_memory_size << std::endl;

	PatternScanner scanner(process_info);
	uintptr_t address = scanner.ScanSignature(PatternScanner::GenerateSignatureFromString("ff 8e ? ? ? ? 48 8b ce e8 ? ? ? ? ff 86"));
	
	std::cout << std::hex << address << std::endl;

	//Patcher::PatchMemory(process_info.m_handle, address, { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 });
}