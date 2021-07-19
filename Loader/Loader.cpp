#include <iostream>
#include "Helpers.h"

int main()
{
    std::uint32_t pid = 0;
    while (pid == 0)
    {
        std::cerr << "Waiting for the Client process..." << std::endl;
        pid = GetPID(L"osclient.exe");
        Sleep(2000);
    }
    std::cerr << "Found Client... PID = " << pid << std::endl;

    return 0;
}
