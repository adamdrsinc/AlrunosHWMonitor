#include "CPUMonitor.h"
//For CPU times
#include <Processthreadsapi.h>
#include <Minwinbase.h>
//Controlling the Console
#include "ConsoleTools.h"

void CPUMonitor::runCPUMonitor()
{
    std::cout
        << "\n-----------------\n"
        << "-- CPU Monitor --\n"
        << "-----------------\n"
        << std::endl;
    
#ifdef _WIN32
    //Windows

    FILETIME idleTime;
    FILETIME kernelTime;
    FILETIME systemTime;
    bool running = true;

    while (running)
    {
        ConsoleTools::clearConsole();


        if (GetSystemTimes(&idleTime, &kernelTime, &systemTime))
        {
            ULARGE_INTEGER uli_idleTime;
            ULARGE_INTEGER uli_kernelTime;
            ULARGE_INTEGER uli_systemTime;

            uli_idleTime.LowPart  = idleTime.dwLowDateTime;
            uli_idleTime.HighPart = idleTime.dwHighDateTime;

            uli_kernelTime.LowPart  = kernelTime.dwLowDateTime;
            uli_kernelTime.HighPart = kernelTime.dwHighDateTime;

            uli_systemTime.LowPart  = systemTime.dwLowDateTime;
            uli_systemTime.HighPart = systemTime.dwHighDateTime;
        }
        else
        {
            std::cout << "ERROR::CPU_TIMES : Could not receive system times.\n";
        }
    }
    



#elif defined (__LINUX__) || defined (__gnu_linux__) || defined (__linux__)
    //Linux
#endif

}