#include "PatternScanner.h"
#include "../../ext/EasyString.h"

uintptr_t PatternScanner::ScanSignature(std::vector<int> signature)
{
    uintptr_t start = m_process_info.m_base_address;
    size_t pos = 0;
    for (uintptr_t addr = start; addr < start + m_process_info.m_memory_size; addr++) {
        for (int i = 0; i < signature.size(); i++) {
            if (signature[i] != -1 && signature[i] != *reinterpret_cast<unsigned char*>(addr + i)) {
                break;
            }
            if (i + 1 == signature.size()) {
                return addr;
            }
        }
    }
    return 0;
}

std::vector<int> PatternScanner::GenerateSignatureFromString(const std::string& signature)
{
    std::vector<int> result;

    std::vector<std::string> split = easystring::split(signature, " ");
    for (const std::string& part : split) {
        if (part == "?") result.push_back(-1);
        else {
            std::string byte = "0x" + part;
            result.push_back(std::strtoul(byte.c_str(), nullptr, 16));
        }
    }

    return result;
}
