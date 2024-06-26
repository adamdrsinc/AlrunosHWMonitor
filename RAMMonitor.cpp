#include "RAMMonitor.h"

void RAMMonitor::runRAMMonitor()
{
    ConsoleTools::clearConsole();

    std::cout
        << "\n-----------------\n"
        << "-- RAM Monitor --\n"
        << "-----------------\n"
        << std::endl;

    //Getting memory statistics from Windows
    MEMORYSTATUSEX memStat;
    memStat.dwLength = sizeof(memStat);
    GlobalMemoryStatusEx(&memStat);

    //Outputting how much total RAM in GB and MB the user has. This is set to 4 decimal places.
    std::cout << "Total RAM (GB): " << std::fixed << std::setprecision(4) << memStat.ullTotalPhys * CONV_GB << std::endl;
    std::cout << "Total RAM (MB): " << std::fixed << std::setprecision(4) << memStat.ullTotalPhys * CONV_MB << std::endl;

    std::chrono::steady_clock::time_point tPoint{ std::chrono::steady_clock::now() };

    char inp{ ' ' };
    bool ramMonitorRunning{ true };
    bool nextTick{ true };
    while (ramMonitorRunning)
    {
        if (nextTick)
        {
            nextTick = false;
            //Getting current time
            tPoint = std::chrono::steady_clock::now();

            GlobalMemoryStatusEx(&memStat);

            //Outputting % usage of RAM.
            std::cout << "Usage (%): " << memStat.dwMemoryLoad << std::endl;
            //Outputting available RAM in MB to user.
            std::cout << "Available (MB): " << std::fixed << std::setprecision(4) << memStat.ullAvailPhys * CONV_MB << std::endl;
            std::cout << "Press q to quit to the main menu." << std::endl;
        }


        //Getting time since last update
        std::chrono::steady_clock::duration timeElapsed = std::chrono::steady_clock::now() - tPoint;

        //If 2.5 seconds have elapsed, update to next tick
        if (std::chrono::duration_cast<std::chrono::milliseconds>(timeElapsed).count() >= 1000)
        {
            nextTick = true;
            ConsoleTools::clearLines(4);
        }


#ifdef _WIN32
        if (GetAsyncKeyState(KB_Q))
        {
            break;
        }
#endif


    }
}

