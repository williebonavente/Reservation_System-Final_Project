#include <stdio.h>
#include <windows.h>

int main()
{
    // Enable support for ANSI escape sequences in Windows console
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    SetConsoleMode(hOut, dwMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);

    // Example of using ASCII color codes
    printf("\033[1;31m"); // Set text color to red (1;31)
    printf("Hello, ");
    printf("\033[1;32m"); // Set text color to green (1;32)
    printf("world!");
    printf("\033[0m"); // Reset text color to default (0)
    printf("\n");

    return 0;
}
