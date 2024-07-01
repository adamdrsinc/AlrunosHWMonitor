#include "CPUMonitor.h"


void CPUMonitor::runCPUMonitor()
{
    ConsoleTools::clearConsole();

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
    bool firstTime = true;

    int previousSecond_SysTime{ 0 };

    

    while (running)
    {

        //Getting current times. These are times which state how many nanoseconds have elapsed since 1601. To convert these, do the following:
        if (GetSystemTimes(&idleTime, &kernelTime, &systemTime))
        {
            SYSTEMTIME systime_SystemTime;
            SYSTEMTIME systime_IdleTime;
            SYSTEMTIME systime_KernelTime;
            GetSystemTime(&systime_SystemTime);
            GetSystemTime(&systime_IdleTime);
            GetSystemTime(&systime_KernelTime);

            if (previousSecond_SysTime != systime_SystemTime.wSecond)
            {
                previousSecond_SysTime = systime_SystemTime.wSecond;

                if (firstTime)
                    firstTime = false;
                else
                    ConsoleTools::clearLines(4);

                std::cout << "System Time: " << systime_SystemTime.wHour << ':' << systime_SystemTime.wSecond << std::endl;
                std::cout << "Idle   Time: " << systime_IdleTime.wHour   << ':' << systime_IdleTime.wSecond   << std::endl;
                std::cout << "Kernel Time: " << systime_KernelTime.wHour << ':' << systime_KernelTime.wSecond << std::endl;
            }

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