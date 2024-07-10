
#include "Utility.h"

void cls(HANDLE hConsole) //clearing the screen (I copied this code from https://learn.microsoft.com/en-us/windows/console/clearing-the-screen)
{
    COORD coordScreen = { 0, 0 };    // home for the cursor
    DWORD cCharsWritten;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD dwConSize;

    // Get the number of character cells in the current buffer.
    if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
    {
        return;
    }

    dwConSize = csbi.dwMaximumWindowSize.X * csbi.dwMaximumWindowSize.Y;

    // Fill the entire screen with blanks.
    if (!FillConsoleOutputCharacter(hConsole,        // Handle to console screen buffer
        (TCHAR)' ',      // Character to write to the buffer
        dwConSize,       // Number of cells to write
        coordScreen,     // Coordinates of first cell
        &cCharsWritten)) // Receive number of characters written
    {
        return;
    }

    // Get the current text attribute.
    if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
    {
        return;
    }

    // Set the buffer's attributes accordingly.
    if (!FillConsoleOutputAttribute(hConsole,         // Handle to console screen buffer
        csbi.wAttributes, // Character attributes to use
        dwConSize,        // Number of cells to set attribute
        coordScreen,      // Coordinates of first cell
        &cCharsWritten))  // Receive number of characters written
    {
        return;
    }

    // Put the cursor at its home coordinates.
    SetConsoleCursorPosition(hConsole, coordScreen);
}


double RegulateDegree(double& value1) {   // If the user enter a degree input higher than 360, it regulates the degree (0-360) 
    int temp = value1 / 360;
    return value1 -= (temp * 360);
}

void DisplayHomeScreen(void) {

    CONSOLE_SCREEN_BUFFER_INFO screen;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &screen);

    SetWindowLong(GetConsoleWindow(), GWL_STYLE, GetWindowLong(GetConsoleWindow(), GWL_STYLE) & ~WS_SIZEBOX);     // Disable maximizing the window 
    SetWindowLong(GetConsoleWindow(), GWL_STYLE, GetWindowLong(GetConsoleWindow(), GWL_STYLE) & ~WS_MAXIMIZEBOX);

    std::string header{ "CALCULATOR WITH ENCODER-DECODER" };

    std::cout << std::setfill('=') << std::setw(screen.dwMaximumWindowSize.X - 1) << "" << std::setfill(' ');       // Display '=' strip  

    std::cout << std::right << "\n" << std::setw((header.size()) + ((screen.dwMaximumWindowSize.X - header.size()) / 2)) << header << "\n"; // Display header

    std::cout << std::setfill('=') << std::setw(screen.dwMaximumWindowSize.X - 1) << "" << std::setfill(' ');        // Display '=' strip  


    std::cout << "\n\n";
    std::cout << std::left << std::setw(screen.dwMaximumWindowSize.X / 2 - header.size() / 4) << "" << "1 - Calculator\n\n"   // Display menu options
        << std::setw(screen.dwMaximumWindowSize.X / 2 - header.size() / 4) << "" << "2 - Encoder\n\n"
        << std::setw(screen.dwMaximumWindowSize.X / 2 - header.size() / 4) << "" << "3 - Decoder\n\n"
        << std::setw(screen.dwMaximumWindowSize.X / 2 - header.size() / 4) << "" << "4 - Exit";

}

