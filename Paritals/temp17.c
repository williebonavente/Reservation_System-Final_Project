#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <conio.h>
#include <Windows.h>

// Constants
#define MAX_ROW 5
#define MAX_COL 4
#define MAX_FILENAME_LENGTH 25
#define MAX_NAME_LENGTH 100
#define MAX_ADDRESS_LENGTH 100

typedef struct
{
    char name[MAX_NAME_LENGTH];
    int age;
    char address[MAX_ADDRESS_LENGTH];
    bool assigned;
} Passenger;

typedef struct
{
    Passenger passenger;
} Seat;

// Step 1
void disp_menu();
void loading_screen();
void inp_filename(char *filename);
void init_sts(Seat ***seats);
void free_sts(Seat ***seats);
void clearScn();

// Step 2 / Case 2
bool validity(int row, char col);
void assigning(Seat ***seats, const char *name, int age, const char *address, int row, char col);
void add_pass(Seat ***seats, const char *filename);
void writing(const char *filename, Seat ***seats);
void reading(const char *filename, Seat ***seats);
void displaying(const Seat **seats);

// Step 3 / Case 3
void showing(const char *filename);
void clearing(const char *filename);
void editing(Seat ***seats, const char *filename);
void appending(const char *filename, const char *name, int age, const char *address, int row, char col);
bool user_login();
void modify_seat_Ass(Seat ***seats, int fromRow, char fromCol, int toRow, char toCol); // Renamed from modify_seat

// Step 4 / Case 4
void canceling(Seat ***seats, const char *filename);

// Menu File Functions - 1
void modifying(Seat ***seats);
void centerAlign(const char *text);
void setConsoleFont(const wchar_t *fontName);
void setConsoleFontSize(int fontSize);
void enableVirtualTerminalProcessing();

// Main function - Driver Function
int main()
{
    Seat **seats = NULL;
    init_sts(&seats);

    int choice;
    char another;

    char filename[MAX_FILENAME_LENGTH];
    inp_filename(filename);

    if (access(filename, F_OK) == -1)
    {
        printf("Error: The file '%s' does not exist.\n", filename);
        free_sts(&seats); // Free the allocated memory before exiting
        return 1;
    }

    else
    {
        bool loggedIn = user_login();
        if (loggedIn)
        {
            do
            {
                clearScn();  // cls
                disp_menu(); // Displaying the menu
                printf("\t\nEnter your choice >> ");
                scanf("%i", &choice);

                switch (choice)
                {
                case 1:
                    clearScn();
                    reading(filename, &seats);
                    displaying((const Seat **)seats);
                    break;
                case 2:
                    clearScn();
                    reading(filename, &seats);
                    add_pass(&seats, filename);
                    break;
                case 3:
                    clearScn();
                    reading(filename, &seats);
                    editing(&seats, filename);
                    break;
                case 4:
                    clearScn();
                    reading(filename, &seats);
                    canceling(&seats, filename);
                    break;
                case 5:
                    clearScn();
                    reading(filename, &seats);
                    showing(filename);
                    break;
                case 6:
                    clearScn();
                    // Program Exiting.
                    printf("\n\n");
                    printf("\033[0;100m"); // Black text on light blue background
                    centerAlign("THIS PROGRAM WAS CREATED BY: WILLIE M. BONAVENTE");
                    centerAlign("BSIT 1-5");
                    printf("\n");
                    centerAlign("THE PROGRAM IS NOW EXITING.");
                    printf("\n\n");
                    printf("\033[0m"); // Reset color to default
                    loading_screen();
                    exit(1);
                    break;

                default:
                    clearScn();
                    printf("\n\t\t\tError! P4lease select a valid option.\t\t\n");
                    printf("\n");
                    break;
                }
                printf("\n\tReturn to Main Menu (Press 'Y') >> ");
                scanf(" %c", &another);
                clearScn();
            } while (another == 'Y' || another == 'y');
        }

        else
        {
            clearScn();
            printf("\n");
            printf("\t\tInvalid password. Login failed.\n");
        }
    }

    // Program Exiting.
    printf("\n\n");
    printf("\033[0;100m"); // Black text on light blue background
    centerAlign("THIS PROGRAM WAS CREATED BY: WILLIE M. BONAVENTE");
    centerAlign("BSIT 1-5");
    printf("\n");
    centerAlign("THE PROGRAM IS NOW EXITING.");
    printf("\n\n");
    printf("\033[0m"); // Reset color to default
    loading_screen();
    free_sts(&seats);
    return 0;

    return 0;
}

void centerAlign(const char *text)
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    int consoleWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    int textWidth = strlen(text);

    int i;

    int padding = (consoleWidth - textWidth) / 2;
    for (i = 0; i < padding; i++)
    {
        putchar(' ');
    }

    printf("%s", text);
}

void setConsoleFont(const wchar_t *fontName)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_FONT_INFOEX fontInfo;
    fontInfo.cbSize = sizeof(CONSOLE_FONT_INFOEX);
    GetCurrentConsoleFontEx(hConsole, FALSE, &fontInfo);

    wcscpy(fontInfo.FaceName, fontName);
    SetCurrentConsoleFontEx(hConsole, FALSE, &fontInfo);
}

void setConsoleFontSize(int fontSize)
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_FONT_INFOEX fontInfo;
    fontInfo.cbSize = sizeof(CONSOLE_FONT_INFOEX);
    GetCurrentConsoleFontEx(hOut, FALSE, &fontInfo);

    fontInfo.dwFontSize.X = fontSize;
    fontInfo.dwFontSize.Y = fontSize;

    SetCurrentConsoleFontEx(hOut, FALSE, &fontInfo);
}

void enableVirtualTerminalProcessing()
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;

    if (GetConsoleMode(hOut, &dwMode))
    {
        dwMode |= 0x0004; // ENABLE_VIRTUAL_TERMINAL_PROCESSING
        SetConsoleMode(hOut, dwMode);
    }
}

void disp_menu()
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);

    enableVirtualTerminalProcessing();

    // Set the font to "Big Money-ne" at the beginning
    setConsoleFont(L"Big Money-ne");

    // Set the font size to 36 for the title
    setConsoleFontSize(24);

    // Enable light green color for the title
    printf("\033[1;92m");
    printf("\n\n");
    printf("\t\t\t\t=============================================================\n");
    centerAlign("WELCOME TO STAIRWAY TO HEAVEN AIRLINE");
    printf("\n\t\t\t\t=============================================================\n");
    printf("\n");

    // Reset color and font size to default
    printf("\033[0m");

    // Enable colors
    printf("\033[1;36;104m");
    printf("\t\t\t\t\t\t\tMAIN MENU\n\n");
    printf("\033[0m");
    printf("\t\t\t\t\t   [%s1%s] Display the Available Seats\n", "\033[1;33m", "\033[0m"); // Yellow color for the option number
    printf("\t\t\t\t\t   [%s2%s] Add Passenger\n", "\033[1;33m", "\033[0m");
    printf("\t\t\t\t\t   [%s3%s] Edit Seat Number\n", "\033[1;33m", "\033[0m");
    printf("\t\t\t\t\t   [%s4%s] Cancel Reservation\n", "\033[1;33m", "\033[0m");
    printf("\t\t\t\t\t   [%s5%s] Display the List of Passengers\n", "\033[1;33m", "\033[0m");
    printf("\t\t\t\t\t   [%s6%s] EXIT\n", "\033[1;33m", "\033[0m");

    // Reset color and font size to default
    printf("\033[0m");
}

void clearScn()
{
#ifdef _WIN32
    system("cls");

#endif
}
void loading_screen()
{
    int i;

    printf("\033[1;33m"); // Yellow color for the countdown numbers
    for (i = 3; i > 0; i--)
    {
        printf("\t\t\t\t\t\t%d...\n", i);
        sleep(1);
    }

    printf("\033[0m"); // Reset color to default

    clearScn();
}

void inp_filename(char *filename)
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    enableVirtualTerminalProcessing();

    // Set the font to "Cascadia Code" at the beginning
    setConsoleFont(L"Cascadia Code");

    // Enable light blue background color for the prompt
    printf("\033[1;44m");

    // Center align the banner
    centerAlign("PLEASE ENTER THE FILENAME TO CONTINUE ON THE PROGRAM");
    printf("\n\n");

    // Center align the prompt
    centerAlign("Please enter the filename: ");

    // Reset color and font style to default
    printf("\033[0m");
    setConsoleFont(L"Consolas");

    fgets(filename, MAX_FILENAME_LENGTH, stdin);
    filename[strcspn(filename, "\n")] = '\0'; // Remove trailing newline character
}

void init_sts(Seat ***seats)
{

    int i, j;
    *seats = (Seat **)malloc(MAX_ROW * sizeof(Seat *));
    for (i = 0; i < MAX_ROW; i++)
    {
        (*seats)[i] = (Seat *)malloc(MAX_COL * sizeof(Seat));
        for (j = 0; j < MAX_COL; j++)
        {
            (*seats)[i][j].passenger.assigned = false;
        }
    }
}
void free_sts(Seat ***seats)

{
    int i;
    // Free dynamically allocated memory for seats
    for (i = 0; i < MAX_ROW; i++)
    {
        free((*seats)[i]);
    }
    free(*seats);
    *seats = NULL;
}

bool validity(int row, char col)
{
    // Check if the given seat is valid
    // Return true if valid, false otherwise
    return row >= 1 && row <= MAX_ROW && col >= 'A' && col <= ('A' + MAX_COL - 1);
}

void assigning(Seat ***seats, const char *name, int age, const char *address, int row, char col)
{
    // Assign the seat to the passenger
    strcpy((*seats)[row - 1][col - 'A'].passenger.name, name);
    (*seats)[row - 1][col - 'A'].passenger.age = age;
    strcpy((*seats)[row - 1][col - 'A'].passenger.address, address);
    (*seats)[row - 1][col - 'A'].passenger.assigned = true;
}

void add_pass(Seat ***seats, const char *filename)
{
    char name[MAX_NAME_LENGTH];
    int age;
    char address[MAX_ADDRESS_LENGTH];
    int row;
    char col;
    char another; // if the user wants to add another record until they terminate

    do
    {
        clearScn();
        displaying((const Seat **)*seats);
        printf("\nEnter passenger name (or press C to cancel): ");
        if (scanf("%s", name) == 1)
        {
            if (strcmp(name, "C") == 0 || strcmp(name, "c") == 0)
            {
                printf("Passenger addition canceled.\n");
                return; // Exit the function without adding the passenger
            }
        }
        else
        {
            printf("Invalid input. Please try again.\n");
            continue; // Restart the loop for name input
        }

        printf("Enter passenger age (or press C to cancel): ");
        if (scanf("%d", &age) != 1)
        {
            char cancel;
            scanf(" %c", &cancel);
            if (cancel == 'C' || cancel == 'c')
            {
                printf("Passenger addition canceled.\n");
                return; // Exit the function without adding the passenger
            }
            else
            {
                printf("Invalid input. Please try again.\n");
                continue; // Restart the loop for age input
            }
        }

        printf("Enter passenger address (or press C to cancel): ");
        if (scanf(" %[^\n]", address) == 1)
        {
            if (strcmp(address, "C") == 0 || strcmp(address, "c") == 0)
            {
                printf("Passenger addition canceled.\n");
                return; // Exit the function without adding the passenger
            }
        }
        else
        {
            printf("Invalid input. Please try again.\n");
            continue; // Restart the loop for address input
        }

        printf("Enter the seat (row column) or press C to cancel: ");
        if (scanf("%d %c", &row, &col) == 2)
        {
            if (validity(row, col) && !(*seats)[row - 1][col - 'A'].passenger.assigned)
            {
                assigning(seats, name, age, address, row, col);

                // Save the seat assignment to a file
                clearScn();
                displaying((const Seat **)*seats);
                assigning(seats, name, age, address, row, col);
                centerAlign("SEAT ASSIGNED SUCESSFULLY.\n");
                centerAlign("\tNAME: ");
                printf("%s\n", name);
                centerAlign("AGE: ");
                printf("%d\n", age);
                centerAlign("\tADDRESS: ");
                printf("%s\n", address);
                centerAlign("\tSEAT: ");
                printf("%d%c\n", row, col);
                appending(filename, name, age, address, row, col);
            }
            else
            {
                printf("Invalid seat assignment or seat already assigned.\n");
            }
        }
        else
        {
            char cancel;
            scanf(" %c", &cancel);
            if (cancel == 'C' || cancel == 'c')
            {
                printf("Passenger addition canceled.\n");
                return; // Exit the function without adding the passenger
            }
            else
            {
                printf("Invalid input. Please try again.\n");
            }
        }

        printf("Do you want to add another record? (Press 'Y') >> ");
        scanf(" %c", &another);
    } while (another == 'Y' || another == 'y');
}

void writing(const char *filename, Seat ***seats)
{
    // Write the seat assignments to a file
    FILE *file = fopen(filename, "w");
    if (file == NULL)
    {
        printf("Error opening file for writing.\n");
        return;
    }

    int i, j;

    for (i = 0; i < MAX_ROW; i++)
    {
        for (j = 0; j < MAX_COL; j++)
        {
            if ((*seats)[i][j].passenger.assigned)
            {
                fprintf(file, "%s\t%d\t%s\t%d%c\n", (*seats)[i][j].passenger.name, (*seats)[i][j].passenger.age,
                        (*seats)[i][j].passenger.address, i + 1, 'A' + j);
            }
        }
    }

    fclose(file);
}

void reading(const char *filename, Seat ***seats)
{
    // Read seat assignments from a file
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Error opening file for reading.\n");
        return;
    }

    else
    {
        char line[100];
        while (fgets(line, sizeof(line), file))
        {
            int row;
            char col;
            char name[MAX_NAME_LENGTH];
            int age;
            char address[MAX_ADDRESS_LENGTH];

            // Reading a file, a condition that must be in order.

            if (sscanf(line, "%s%d%s%d%c", name, &age, address, &row, &col) == 5)
            {
                if (validity(row, col))
                {
                    assigning(seats, name, age, address, row, col);
                    // Assign age and address to the assigned passenger
                    strcpy((*seats)[row - 1][col - 'A'].passenger.name, name);
                    (*seats)[row - 1][col - 'A'].passenger.age = age;
                    strcpy((*seats)[row - 1][col - 'A'].passenger.address, address);
                }
            }
        }

        fclose(file);
    }
}

void displaying(const Seat **seats)
{
    int terminalWidth = 80;
    int headerWidth = strlen("Seat Map Availability");
    int seatMapWidth = MAX_COL * 8 + 1;

    // Calculate the number of spaces needed to center the header.
    int paddingHeader = (terminalWidth - headerWidth) / 2;

    // Set the title banner color to cyan
    printf("\033[1;36m");
    printf("\n\n");

    // Calculate the padding for the horizontal lines
    int paddingLine = (terminalWidth - seatMapWidth) / 2;

    // First horizontal line
    printf("%*s---------------------------------\n", paddingLine, "");

    // Header
    printf("%*s%s\n", paddingHeader, "", "Seat Map Availability");

    // Second horizontal line
    printf("%*s---------------------------------\n", paddingLine, "");

    // Set the letters' color to light green
    printf("\033[1;92m");

    // Calculate the number of spaces needed to center the seat map
    int paddingSeatMap = (terminalWidth - seatMapWidth) / 2;
    int i, j;

    // Calculate the maximum width of the seat letter
    int maxSeatLetterWidth = 0;
    for (j = 0; j < MAX_COL; j++)
    {
        int seatLetterWidth = snprintf(NULL, 0, "%c", 'A' + j);
        if (seatLetterWidth > maxSeatLetterWidth)
        {
            maxSeatLetterWidth = seatLetterWidth;
        }
    }

    // Calculate the padding for seat letters
    int paddingSeatLetter = maxSeatLetterWidth + 2; // Adding 2 for extra spacing

    for (i = 0; i < MAX_ROW; i++)
    {
        // Set the numbers' color to white
        printf("\033[1;97m");
        printf("%*s%d", paddingSeatMap, "", i + 1);

        // Reset the color to light green
        printf("\033[1;92m");

        for (j = 0; j < MAX_COL; j++)
        {
            if (seats[i][j].passenger.assigned)
            {
                // Change the color to bright red for occupied seats
                printf("\033[1;91m");
                printf("%*sX", paddingSeatLetter - 1, ""); // Using -1 to adjust for the 'X'
            }
            else
            {
                printf("%*s%c", paddingSeatLetter, "", 'A' + j);
            }

            // Reset the color to light green
            printf("\033[1;92m");
        }
        printf("\n%*s---------------------------------\n", paddingSeatMap, "");
    }
    printf("\n");

    // Reset the color to default
    printf("\033[0m");
}

void showing(const char *filename)
{
    int count = 0;

    // Enable cyan color for the title with a light blue background
    printf("\033[1;36;104m");
    printf("\n\t\t\tList of Passengers\t\t\n");
    printf("\033[0m"); // Reset color to default

    printf("\n");
    printf("\033[1;36;101m");
    printf("\t%4s%-14s%-15s%-16s%-5s\n", " ", "Name", "Age", "Address", "Seat");
    printf("\n");

    // Open the file for reading
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Error opening file for reading.\n");
        return;
    }

    // Read and display each line from the file
    char line[100];
    while (fgets(line, sizeof(line), file))
    {
        char name[MAX_NAME_LENGTH];
        int age;
        char address[MAX_ADDRESS_LENGTH];
        int row;
        char col;

        // Parse the line and extract the information
        if (sscanf(line, "%s%d%s%d%c", name, &age, address, &row, &col) == 5)
        {
            count++;

            // Enable white color for the passenger records with a light gray background
            printf("\033[1;97;100m");
            printf("\t%d. %-15s%-15d%-17s%d%c\n", count, name, age, address, row, col);
            printf("\033[0m"); // Reset color to default
        }
    }

    fclose(file);

    if (count == 0)
    {
        printf("No passenger records found.\n");
    }
}

void clearing(const char *filename)
{
    // Clear the content of the file
    FILE *file = fopen(filename, "w");
    if (file == NULL)
    {
        printf("Error opening file for writing.\n");
        return;
    }

    fclose(file);
}
void appending(const char *filename, const char *name, int age, const char *address, int row, char col)
{
    // Append seat assignment to the file
    FILE *file = fopen(filename, "a");
    if (file == NULL)
    {
        printf("Error opening file for writing.\n");
        return;
    }

    fprintf(file, "%s\t%d\t\t%s\t\t%d%c\n", name, age, address, row, col);

    fclose(file);
}

void modifying(Seat ***seats)
{
    // Modify the seat assignment
    printf("Enter the row and column of the seat to modify (e.g., 1A): ");
    int row;
    char col;
    scanf("%d %c", &row, &col);

    if (validity(row, col))
    {
        if ((*seats)[row - 1][col - 'A'].passenger.assigned)
        {
            printf("Enter the new name for the seat: ");
            char newName[MAX_NAME_LENGTH];
            scanf(" %[^\n]", newName);

            printf("Enter the new age for the passenger: ");
            int newAge;
            scanf("%d", &newAge);

            printf("Enter the new address for the passenger: ");
            char newAddress[MAX_ADDRESS_LENGTH];
            scanf(" %[^\n]", newAddress);

            assigning(seats, newName, newAge, newAddress, row, col);
            printf("Seat modified successfully.\n");

            printf("Enter the filename to save seat assignments: ");
            char filename[MAX_FILENAME_LENGTH];
            scanf(" %[^\n]", filename);
            writing(filename, (Seat ***)seats);
        }
        else
        {
            printf("The seat is not assigned.\n");
        }
    }
    else
    {
        printf("Invalid seat.\n");
    }
}

bool user_login()
{
    // Set the font to "Cascadia Code" at the beginning
    setConsoleFont(L"Cascadia Code");

    // Enable light blue background color for the banner
    printf("\033[1;44m");

    // Center align the banner with animation
    printf("\n\n");
    int i;
    for (i = 0; i < 25; i++)
    {
        if (i % 5 == 0)
        {
            printf("\r");
            centerAlign("PLEASE ENTER THE PASSWORD TO CONTINUE");
            printf("\n\n");
        }
        Sleep(100); // Add a small delay for animation effect
    }

    // Reset color and font style to default
    printf("\033[0m");

    // Enable light green color for the prompt
    printf("\033[1;92m");

    // Center align the prompt
    centerAlign("Enter the password: ");

    // Reset color and font style to default
    printf("\033[0m");

    // Read the password input with asterisks
    char password[20];
    i = 0;
    while (1)
    {
        char c = getch(); // Read a character without echoing to the console
        if (c == '\r' || c == '\n')
        {
            password[i] = '\0';
            break;
        }
        else if (c == '\b')
        {
            if (i > 0)
            {
                printf("\b \b"); // Erase the last asterisk
                i--;
            }
        }
        else
        {
            password[i++] = c;
            printf("*"); // Print an asterisk instead of the actual character
        }
    }

    // Reset color and font style to default
    printf("\033[0m");

    // Check if the entered password is correct
    if (strcmp(password, "password123") == 0)
    {
        // Enable green color for the login successful message
        printf("\033[1;92m");

        // Center align the login successful message with animation
        printf("\n\n");
        for (i = 0; i < 20; i++)
        {
            if (i % 4 == 0)
            {
                printf("\r");
                centerAlign("LOGIN SUCCESSFUL!");
                printf("\n\n");
            }
            Sleep(200); // Add a small delay for animation effect
        }

        // Reset color and font style to default
        printf("\033[0m");

        return true;
    }
    else
    {
        // Enable red color for the login failed message
        printf("\033[1;91m");

        // Center align the login failed message with animation
        printf("\n\n");

        int i;
        for (i = 0; i < 20; i++)
        {
            if (i % 4 == 0)
            {
                printf("\r");
                centerAlign("LOGIN FAILED! PLEASE TRY AGAIN");
                printf("\n\n");
            }
            Sleep(200); // Add a small delay for animation effect
        }

        // Reset color and font style to default
        printf("\033[0m");

        return false;
    }
}

void editing(Seat ***seats, const char *filename)
{
    int fromRow;
    char fromCol;
    int toRow;
    char toCol;
    char cancel;

    while (true)
    {
        displaying((const Seat **)*seats); // guiding the user.
        printf("Enter the current seat number (row column) or press C to cancel: ");
        if (scanf("%d %c", &fromRow, &fromCol) == 2)
        {
            printf("Enter the new seat number (row column): ");
            scanf("%d %c", &toRow, &toCol);

            if (validity(fromRow, fromCol) && validity(toRow, toCol) &&
                (*seats)[fromRow - 1][fromCol - 'A'].passenger.assigned &&
                !(*seats)[toRow - 1][toCol - 'A'].passenger.assigned)
            {
                modify_seat_Ass(seats, fromRow, fromCol, toRow, toCol);
                clearScn();
                printf("Seat number modified successfully.\n");
                printf("Seat %d%c has been changed to %d%c\n", fromRow, fromCol, toRow, toCol);
                writing(filename, (Seat ***)seats);
            }
            else
            {
                clearScn();
                printf("Invalid seat numbers or seat assignment. Please try again.\n");
            }
        }
        else
        {
            // Check if the user entered 'C' or 'c' to cancel
            scanf(" %c", &cancel);
            if (cancel == 'C' || cancel == 'c')
            {
                printf("Seat modification canceled.\n");
                return; // Exit the function without modifying the seat
            }
            else
            {
                clearScn();
                printf("Invalid input. Please try again.\n");
            }
        }
    }
}

void modify_seat_Ass(Seat ***seats, int fromRow, char fromCol, int toRow, char toCol)
{
    (*seats)[toRow - 1][toCol - 'A'].passenger = (*seats)[fromRow - 1][fromCol - 'A'].passenger;
    (*seats)[fromRow - 1][fromCol - 'A'].passenger.assigned = false;
    (*seats)[fromRow - 1][fromCol - 'A'].passenger.name[0] = '\0';
}

void canceling(Seat ***seats, const char *filename)
{
    int row;
    char col;
    char cancel;
    clearScn();

    do
    {
        showing(filename);

        printf("\nEnter the seat to cancel (row column) or press C to cancel: ");
        if (scanf("%d %c", &row, &col) != 2)
        {
            scanf(" %c", &cancel);
            if (cancel == 'C' || cancel == 'c')
            {
                printf("Cancellation canceled.\n");
                return; // Exit the function without canceling any reservation
            }
            else
            {
                clearScn();
                printf("Invalid input. Please enter a valid seat number or 'C' to cancel.\n");
                continue; // Restart the loop to prompt for a valid seat number
            }
        }

        if (validity(row, col) && (*seats)[row - 1][col - 'A'].passenger.assigned)
        {
            // Store the details of the canceled reservation in variables
            char canceledName[MAX_NAME_LENGTH];
            int canceledAge;
            char canceledAddress[MAX_ADDRESS_LENGTH];

            strcpy(canceledName, (*seats)[row - 1][col - 'A'].passenger.name);
            canceledAge = (*seats)[row - 1][col - 'A'].passenger.age;
            strcpy(canceledAddress, (*seats)[row - 1][col - 'A'].passenger.address);

            // Now, cancel the reservation by setting the assigned passenger values to empty
            (*seats)[row - 1][col - 'A'].passenger.assigned = false;
            (*seats)[row - 1][col - 'A'].passenger.name[0] = '\0';

            // Save the updated seat assignment to the file
            clearScn();
            printf("Reservation canceled successfully.\n");
            writing(filename, (Seat ***)seats);

            // Print the details of the canceled reservation
            printf("Canceled Reservation Details:\n");
            printf("Name: %s\n", canceledName);
            printf("Age: %d\n", canceledAge);
            printf("Address: %s\n", canceledAddress);
        }

        else
        {
            clearScn();
            printf("\n\t\tInvalid seat or seat is not assigned.\n");
        }

    } while (1); // Continue the loop until a valid seat is canceled or the user cancels the cancellation process with 'C'

    clearScn();
}
