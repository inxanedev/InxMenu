#pragma once
#include <Windows.h>
#include <vector>
#include "../ProcessInfo.h"
#include <string>

class PatternScanner
{
public:
	PatternScanner(ProcessInfo& process_info) : m_process_info(process_info) {};
	uintptr_t ScanSignature(std::vector<int> signature);
	static std::vector<int> GenerateSignatureFromString(const std::string& signature);
	ProcessInfo& m_process_info;
};