#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <Windows.h>
#include <iomanip>
#include <chrono>

//Conversions from Byte to X. Do (bytes * CONV_X) for conversion.
#define CONV_GB 9.3132257461548E-10
#define CONV_MB 1.0E-6

//Keyboard Definitions
#define KB_Q 0x51

void runCPUMonitor();
void runRAMMonitor();
void clearConsole();
void clearLines(int count);
bool checkIsNumber(std::string uInp);
std::string menuOptionToString(MenuOption option);

enum MenuOption
{
    ALL,
    MAIN_STORAGE,
    CPU,
    GPU,
    RAM,
    QUIT,
    COUNT_ENUM
};



int main()
{
    //Initialising and defining key variables.
    float versionNumber{ 0.1f };  

    bool running = true;
    while (running)
    {
        clearConsole();

        //Start
        std::cout << "Alrunos Hardware Monitor v." << versionNumber << std::endl;

        std::string userSelection{ "-1" };

        std::cout << "Select an option:\n";
        for (int i = 0; i < MenuOption::COUNT_ENUM; ++i)
        {
            auto currentEnum{ static_cast<MenuOption>(i) };
            std::cout << currentEnum+1 << ". " << menuOptionToString(currentEnum) << std::endl;
        }

        bool isValid = false;
        bool isNumber = false;
        while (isValid == false && isNumber == false)
        {
            std::getline(std::cin, userSelection);

            if (userSelection.empty())
            {
                std::cout << "Enter a value." << std::endl;
                continue;
            }
            
            if (checkIsNumber(userSelection))
            {
                isNumber = true;
                if (std::stoi(userSelection) >= 0 && std::stoi(userSelection) <= MenuOption::COUNT_ENUM)
                {
                    isValid = true;
                }
                else
                {
                    std::cout << "Input a valid option." << std::endl;
                    isValid = false;
                }
            }
            else
            {
                isNumber = false;
                std::cout << "Input a number." << std::endl;
            }
        }

        int enumSelection = std::stoi(userSelection) - 1;
        switch (enumSelection)
        {
        case MenuOption::ALL:
            break;
        case MenuOption::MAIN_STORAGE:
            break;
        case MenuOption::CPU:
            break;
        case MenuOption::GPU:
            break;
        case MenuOption::RAM:
            runRAMMonitor();
            break;
        case MenuOption::QUIT:
            std::cout << "Quitting..." << std::endl;
            return 0;
        }

    }

    return 0;
    
}

void runCPUMonitor()
{
    
}

void runRAMMonitor()
{
    clearConsole();

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

    char inp{' '};
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
            clearLines(4);
        }
            

#ifdef _WIN32
        if (GetAsyncKeyState(KB_Q))
        {
            break;
        }           
#endif

        
    }
}

void clearConsole()
{
#ifdef _WIN32
    system("cls");
#elif defined (__LINUX__) || defined (__gnu_linux__) || defined (__linux__)
    system("clear");
#elif defined (__APPLE__)
    system("clear");
#endif
}

void clearLines(int count) {
    if (count > 0) {
        std::cout << "\x1b[2K"; // Delete current line
        // i=1 because we included the first line
        for (int i = 1; i < count; i++) {
            std::cout
                << "\x1b[1A" // Move cursor up one
                << "\x1b[2K"; // Delete the entire line
        }
        std::cout << "\r"; // Resume the cursor at beginning of line
    }
}

bool checkIsNumber(std::string uInp)
{
    return (uInp.find_first_not_of("0123456789") == std::string::npos);
}

std::string menuOptionToString(MenuOption option)
{
    switch (option)
    {
    case ALL:
        return "All";
        break;
    case MAIN_STORAGE:
        return "Main Storage";
        break;
    case CPU:
        return "CPU";
        break;
    case GPU:
        return "GPU";
        break;
    case RAM:
        return "RAM";
        break;
    case QUIT:
        return "Quit";
        break;
    default:
        return "FAIL";

    }
}
