#pragma once
#include "../patching/PatternScanner.h"
class GUI {
public:
	GUI(ProcessInfo& info) : m_scanner(info), m_is_open(false) {};

	bool m_is_open;
	void Render();

	PatternScanner m_scanner;
};