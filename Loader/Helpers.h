#pragma once
#include <Windows.h>
#include <TlHelp32.h>
#include <cstdint>
#include <string>

std::uint32_t GetPID(const std::wstring&& processName);
void InjectDll(std::uint32_t pid);