// Encryption of Password
#include <stdio.h>
#include <conio.h>

#define MAX_PASSWORD_LENGTH 20

void censorPassword(char *password)
{
    int i = 0;
    while (password[i] != '\0')
    {
        password[i] = '*';
        i++;
    }
}

void getPassword(char *password)
{
    int i = 0;
    char ch;

    while (1)
    {
        ch = getch();
        if (ch == '\r' || ch == '\n') // Check for Enter key press
            break;

        if (ch == '\b' && i > 0) // Check for Backspace key press
        {
            i--;
            password[i] = '\0';
            printf("\b \b"); // Erase the character from console
        }
        else if (ch != '\b' && i < MAX_PASSWORD_LENGTH - 1)
        {
            password[i] = ch;
            i++;
            printf("*"); // Print asterisk to console
        }
    }

    password[i] = '\0';
}

int main()
{
    char password[MAX_PASSWORD_LENGTH];

    printf("Password: ");
    getPassword(password);

    censorPassword(password);
    printf("\nCensored Password: %s\n", password);

    return 0;
}
