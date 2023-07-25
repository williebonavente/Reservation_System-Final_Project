#include <Windows.h>
#include <stdio.h>

int main()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // Get the current console font info
    CONSOLE_FONT_INFOEX fontInfo;
    fontInfo.cbSize = sizeof(CONSOLE_FONT_INFOEX);
    GetCurrentConsoleFontEx(hConsole, FALSE, &fontInfo);

    // Change the font size and name
    fontInfo.dwFontSize.X = 12;                  // Width of the font in pixels
    fontInfo.dwFontSize.Y = 16;                  // Height of the font in pixels
    wcscpy(fontInfo.FaceName, L"Cascadia Code"); // Set the font name to "Cascadia Code"

    // Set the new font info
    SetCurrentConsoleFontEx(hConsole, FALSE, &fontInfo);

    // Output text with the new font
    printf("Hello, this text is displayed using the Cascadia Code font!\n");
     printf("\n");
    printf("=============================================================\n");
    printf("  ____  _            _     ____            _       _         \n");
    printf(" / ___|(_) __ _ _ __| | __/ ___|  ___ _ __(_)_ __ | |_ _   _ \n");
    printf("| |   | | '__| '__| |/ /\\___ \\ / __| '__| | '_ \\| __| | | |\n");
    printf("| |___| | |  | |  |   <  ___) | (__| |  | | |_) | |_| |_| |\n");
    printf(" \\____|_|_|  |_|  |_|\\_\\|____/ \\___|_|  |_| .__/ \\__|\\__, |\n");
    printf("                                          |_|      |___/    \n");
    printf("=============================================================\n");
    printf("\n");
    return 0;
}
