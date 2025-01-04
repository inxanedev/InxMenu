#include "Patch.h"
#include "../ProcessInfo.h"
#include "PatternScanner.h"
#include <iostream>

Patch::Patch(const std::string& signature, int offset, safetyhook::MidHookFn function)
{
	ProcessInfo info;
	PatternScanner scanner(info);

	m_address = scanner.ScanSignature(PatternScanner::GenerateSignatureFromString(signature)) + offset;

	m_on = false;
	m_patch = function;
}

bool Patch::Toggle() {
	if (m_on) {
		m_hook = {};
	}
	else {
		m_hook = safetyhook::create_mid(m_address, m_patch);
	}

	m_on = !m_on;
	return m_on;
}
