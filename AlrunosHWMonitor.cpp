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

//#define MB 1048576
//#define GB 9.3132257461548E-10

void runCPUMonitor();
void runRAMMonitor();
void clearConsole();
void returnToMainMenu();
void clearLines(int count);

struct MenuOptions {
    const std::string MAIN_STORAGE{ "main storage" };
    const std::string ALL         { "all" };
    const std::string CPU         { "cpu" };
    const std::string GPU         { "gpu" };
    const std::string RAM         { "ram" };
    const std::string QUIT        { "quit" };
    const std::string ADD_MENU_SHORTCUT{ "add menu shortcut" };
    const std::vector<std::string> SELECTIONS_VECTOR{ ALL, MAIN_STORAGE, CPU, GPU, RAM, ADD_MENU_SHORTCUT, QUIT };

};


int main()
{
    //Initialising and defining key variables.
    float versionNumber{ 0.1f };  
    MenuOptions menuOptions;

    std::multimap<std::string, std::string> menuInputs;
    //All
    menuInputs.insert(std::pair<std::string, std::string>(menuOptions.ALL,          menuOptions.ALL));
    //CPU
    menuInputs.insert(std::pair<std::string, std::string>(menuOptions.CPU,          menuOptions.CPU));
    //GPU
    menuInputs.insert(std::pair<std::string, std::string>(menuOptions.GPU,          menuOptions.GPU));
    //Main Storage
    menuInputs.insert(std::pair<std::string, std::string>(menuOptions.MAIN_STORAGE, menuOptions.MAIN_STORAGE));
    menuInputs.insert(std::pair<std::string, std::string>("main", menuOptions.MAIN_STORAGE));
    //RAM
    menuInputs.insert(std::pair<std::string, std::string>(menuOptions.RAM,          menuOptions.RAM));
    //Quit
    menuInputs.insert(std::pair<std::string, std::string>(menuOptions.QUIT,         menuOptions.QUIT));
    menuInputs.insert(std::pair<std::string, std::string>("q", menuOptions.QUIT));
    //Add Menu Shortcuts
    menuInputs.insert(std::pair<std::string, std::string>("shortcut", menuOptions.ADD_MENU_SHORTCUT));
    menuInputs.insert(std::pair<std::string, std::string>(menuOptions.ADD_MENU_SHORTCUT, menuOptions.ADD_MENU_SHORTCUT));
    menuInputs.insert(std::pair<std::string, std::string>("add", menuOptions.ADD_MENU_SHORTCUT));


    bool running = true;
    while (running)
    {
        clearConsole();
        //Start
        std::cout << "Alrunos Hardware Monitor v." << versionNumber << std::endl;

        std::string userSelection{ "" };

        std::cout << "Select an option:\n";
        for (int i = 0; i < menuOptions.SELECTIONS_VECTOR.size(); ++i)
        {
            std::cout << "- " << menuOptions.SELECTIONS_VECTOR[i] << std::endl;
        }

        std::cin >> userSelection;

        while (menuInputs.count(userSelection) == 0)
        {
            std::cout << "Please select a valid option." << std::endl;
            std::cin >> userSelection;
        }

        auto itr = menuInputs.find(userSelection);
        std::string userSelectedValue{itr->second};

        //Going to user selected area
        if (userSelectedValue == menuOptions.ALL)
        {

        }
        else if (userSelectedValue == menuOptions.CPU)
        {
            runCPUMonitor();
        }
        else if (userSelectedValue == menuOptions.GPU)
        {

        }
        else if (userSelectedValue == menuOptions.MAIN_STORAGE)
        {

        }
        else if (userSelectedValue == menuOptions.RAM)
        {
            runRAMMonitor();
        }
        else if (userSelectedValue == menuOptions.ADD_MENU_SHORTCUT) 
        {

        }
        else if (userSelectedValue == menuOptions.QUIT)
        {
            std::cout << "Quitting..." << std::endl;
            break;
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

    std::chrono::steady_clock::time_point tPoint{ std::chrono::steady_clock::now() };

    char inp{' '};
    bool ramMonitorRunning{ true };
    bool nextTick{ true };
    while (ramMonitorRunning)
    {
        if (nextTick)
        {
            nextTick = false;
            tPoint = std::chrono::steady_clock::now();

            MEMORYSTATUSEX memStat;
            memStat.dwLength = sizeof(memStat);
            GlobalMemoryStatusEx(&memStat);

            std::cout << "Total RAM (GB): " << std::fixed << std::setprecision(4) << memStat.ullTotalPhys * CONV_GB << std::endl;
            std::cout << "Total RAM (MB): " << std::fixed << std::setprecision(4) << memStat.ullTotalPhys * CONV_MB << std::endl;
            std::cout << "Usage (%): " << memStat.dwMemoryLoad << std::endl;
            std::cout << "Available (MB): " << std::fixed << std::setprecision(4) << memStat.ullAvailPhys * CONV_MB << std::endl;
            std::cout << "Press q to quit to the main menu." << std::endl;
        }
        

        std::chrono::steady_clock::duration timeElapsed = std::chrono::steady_clock::now() - tPoint;
        
        if (std::chrono::duration_cast<std::chrono::milliseconds>(timeElapsed).count() >= 2500)
        {
            nextTick = true;
            clearLines(6);
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

void returnToMainMenu()
{

}

