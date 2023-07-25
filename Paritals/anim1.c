#include <stdio.h>
#include <unistd.h> // For sleep function (Unix/Linux)

void clearScreen()
{
    // Escape code to clear the console screen
    printf("\033[2J");
    printf("\033[H");
}

int main()
{
    // Clear the screen before starting the animation
    clearScreen();

    int screenWidth = 80;
    int characterPosition = 0;
    char character = '@';

    while (1) // Infinite loop for continuous animation
    {
        // Clear the screen before redrawing the character
        clearScreen();

        // Print spaces before the character to move it across the screen
        for (int i = 0; i < characterPosition; i++)
        {
            printf(" ");
        }

        // Print the character at its current position
        printf("%c\n", character);

        // Move the character one position to the right
        characterPosition++;

        // If the character goes beyond the screen width, reset its position
        if (characterPosition >= screenWidth)
        {
            characterPosition = 0;
        }

        // Add a small delay to control the animation speed
        usleep(100000); // 100,000 microseconds (100 milliseconds)
    }

    return 0;
}
