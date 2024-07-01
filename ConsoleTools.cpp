#include "ConsoleTools.h"

void ConsoleTools::clearConsole()
{
#ifdef _WIN32
    system("cls");
#elif defined (__LINUX__) || defined (__gnu_linux__) || defined (__linux__)
    system("clear");
#endif
}

void ConsoleTools::clearLines(int count) {
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