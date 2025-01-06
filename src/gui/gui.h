#pragma once
#include "../patching/PatternScanner.h"
class GUI {
public:
	GUI(ProcessInfo& info) : m_scanner(info), m_is_open(false) {};

	bool m_is_open;
	void Render();

	bool m_initialized_offsets = false;

	PatternScanner m_scanner;

	void InitializeOffsets();
};