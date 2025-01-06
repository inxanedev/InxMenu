#pragma once

#include "../patching/PatternScanner.h"
#include <iostream>
#include <vector>
#include <fstream>

template <typename T>
class Offset
{
public:
	Offset(uintptr_t base_address, uint32_t first_offset, std::vector<uint32_t> offsets) {
		uintptr_t start = base_address + first_offset;
		for (int i = 0; i < offsets.size(); i++) {
			uint32_t offset = offsets[i];
			start += offset;
			if (i == offsets.size() - 1) {
				break;
			}
			start = *((uintptr_t*)start);
		}

		m_address = (T*)start;

		SaveCurrent();
	}

	T* m_address;
	T m_original;

	void SetValue(T value) {
		*m_address = value;
	}

	void Reset() {
		*m_address = m_original;
	}

private:
	void SaveCurrent() {
		m_original = *m_address;
	}
};