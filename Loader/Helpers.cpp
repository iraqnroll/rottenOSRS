#pragma once
#include "Helpers.h"

std::uint32_t GetPID(const std::wstring&& processName) 
{
    std:uint32_t pid = 0;

    // Create snapshot
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    // Check if the snapshot is valid, otherwise bail out
    if (hSnap == INVALID_HANDLE_VALUE)
        return 0;

    PROCESSENTRY32 procEntry{};
    procEntry.dwSize = sizeof(PROCESSENTRY32);

    // Iterate over all processes in the snapshot
    if (Process32First(hSnap, &procEntry)) 
    {
        do 
        {
            // Check if current process name is the same as the passed in process name
            if (_wcsicmp(procEntry.szExeFile, processName.c_str()) == 0) 
            {
                pid = procEntry.th32ProcessID;
                break;
            }
        } while (Process32Next(hSnap, &procEntry));
    }

    // Cleanup
    CloseHandle(hSnap);

    return pid;
}

int InjectDll(std::uint32_t pid)
{
    //Get the handle with pid
    HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);

    //Allocate memory for .dll path
    void* injectedDllPathRemote = VirtualAllocEx(hProc, 0x00, MAX_PATH, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

    if (injectedDllPathRemote == nullptr)
    {
        return 1;
    }
    else
    {
        constexpr const char* dllPath = "\rottenOSRS.dll";
        WriteProcessMemory(hProc, injectedDllPathRemote, dllPath, strlen(dllPath) + 1, 0);
        return 0;
    }
}

