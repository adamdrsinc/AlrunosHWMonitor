#include <iostream>
#include <string>
#include "ConsoleTools.h"
#include "RAMMonitor.h"

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

//Forward declarations
bool checkIsNumber(std::string uInp);
std::string menuOptionToString(MenuOption option);



int main()
{
    //Initialising and defining key variables.
    float versionNumber{ 0.1f };  

    bool running = true;
    while (running)
    {
        ConsoleTools::clearConsole();

        //Start
        std::cout << "Alrunos Hardware Monitor v." << versionNumber << std::endl;


        std::cout << "Select an option:\n";
        for (int i = 0; i < MenuOption::COUNT_ENUM; ++i)
        {
            auto currentEnum{ static_cast<MenuOption>(i) };
            std::cout << currentEnum+1 << ". " << menuOptionToString(currentEnum) << '\n';
        }

        std::string userSelection{ "" };
        bool isValid = false;
        bool isNumber = false;
        while (isValid == false || isNumber == false)
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
                //TODO: FIX
                int userSelection_Int{ std::stoi(userSelection) };
                if ((userSelection_Int >= 0) && (userSelection_Int <= MenuOption::COUNT_ENUM))
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
        {
            RAMMonitor::runRAMMonitor();
            break;
        }
            
        case MenuOption::QUIT:
            std::cout << "Quitting..." << std::endl;
            return 0;
        }

    }

    return 0;
    
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
