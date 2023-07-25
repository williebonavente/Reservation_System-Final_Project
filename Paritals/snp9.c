#include <stdio.h>
#include <windows.h>

// Function to set the console color
void setConsoleColor(WORD color)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

int main()
{
    // Set the background color to light blue (Cyan)
    setConsoleColor(FOREGROUND_GREEN | FOREGROUND_BLUE | BACKGROUND_BLUE | BACKGROUND_INTENSITY);

    // Print some text with the new background color
    printf("Hello, world!\n");

    // Reset the color to default
    setConsoleColor(FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE);

    // Print more text with the default background color
    printf("This is the default background color.\n");

    return 0;
}
