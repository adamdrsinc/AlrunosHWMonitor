// AlrunosHWMonitor.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>
#include <map>


struct HardwareSelections {
    const std::vector<std::string> SELECTIONS_VECTOR{ALL, MAIN_STORAGE, CPU, GPU, RAM, QUIT};
    const std::string MAIN_STORAGE{ "main storage" };
    const std::string ALL         { "all" };
    const std::string CPU         { "cpu" };
    const std::string GPU         { "gpu" };
    const std::string RAM         { "ram" };
    const std::string QUIT        { "quit" };
};

int main()
{
    float versionNumber{ 0.1f };  
    HardwareSelections hwSelections;


    std::multimap<std::string, std::string> hardwareOptions;
    hardwareOptions.insert(std::pair<std::string, std::string>("all",          hwSelections.ALL));
    hardwareOptions.insert(std::pair<std::string, std::string>("cpu",          hwSelections.CPU));
    hardwareOptions.insert(std::pair<std::string, std::string>("gpu",          hwSelections.GPU));
    hardwareOptions.insert(std::pair<std::string, std::string>("main storage", hwSelections.MAIN_STORAGE));
    hardwareOptions.insert(std::pair<std::string, std::string>("main",         hwSelections.MAIN_STORAGE));
    hardwareOptions.insert(std::pair<std::string, std::string>("ram",          hwSelections.RAM));
    hardwareOptions.insert(std::pair<std::string, std::string>("quit",         hwSelections.QUIT));



    std::cout << "Alrunos Hardware Monitor v. " << versionNumber << '\n';


    bool running = true;
    while (running)
    {
        std::string userSelection{ "" };

        std::cout << "Select an option:\n";
        for (const std::string selection : hwSelections.SELECTIONS_VECTOR)
        {
            std::cout << "- " << selection << '\n';
        }
        std::cin >> userSelection;
        while()
    }
    
}

