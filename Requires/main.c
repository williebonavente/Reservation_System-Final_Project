#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

// Constants
#define MAX_ROW 5
#define MAX_COL 4
#define MAX_FILENAME_LENGTH 25
#define MAX_NAME_LENGTH 100
#define MAX_ADDRESS_LENGTH 100

// Struct definitions
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

// Function declarations
// Option 1
void showMenu();
void loadingScreen();
void inputFilename(char *filename);
void initializeSeats(Seat ***seats);
void freeSeats(Seat ***seats);
void clearScreen();
// Step 2 / Case 2
void addPassenger(Seat ***seats, const char *filename);
bool isSeatValid(int row, char col);
void assignSeat(Seat ***seats, const char *name, int age, const char *address, int row, char col);
void displaySeats(const Seat **seats);
void writeToFile(const char *filename, Seat ***seats);
void readFromFile(const char *filename, Seat ***seats);

// Step 3  / Case 3
void editSeatNumber(Seat ***seats, const char *filename);
void modifySeat(Seat ***seats, int fromRow, char fromCol, int toRow, char toCol);

// Step 4 / Case 4
void cancelReservation(Seat ***seats, const char *filename);

// Menu File Functions - 1
void showFileContent(const char *filename);
void clearFile(const char *filename);
void appendToFile(const char *filename, const char *name, int age, const char *address, int row, char col);
void modifySeatAssignment(Seat ***seats);
bool userLogin();

// Main function - Driver Function
int main()
{
    Seat **seats = NULL;
    initializeSeats(&seats);

    int choice;   // choice by the user on the menu.
    char another; //  if the user want to continue.

    // get the filename from the user
    char filename[MAX_FILENAME_LENGTH];
    inputFilename(filename);

    // Step 0: User login with correct password

    // continue with the remaining steps if logged in successfully

    if (access(filename, F_OK) == -1)
    {
        printf("Error: The file '%s' does not exist.\n", filename);
        return 1; // Exit the program with an error code
    }

    else
    {
        bool loggedIn = userLogin();
        if (loggedIn)
        {
            loadingScreen();
            do
            {
                // Step 1: Display the Menu first.
                clearScreen();
                showMenu();
                printf("\t\nEnter your choice >> ");
                scanf("%i", &choice);

                switch (choice)
                {
                case 1:
                    // Step 2: Display available seats
                    clearScreen();
                    readFromFile(filename, &seats);
                    displaySeats((const Seat **)seats);
                    break;
                case 2:
                    // Step 3: Add passengers
                    clearScreen();
                    addPassenger(&seats, filename);
                    break;
                case 3:
                    // Step 4: Edit seat number
                    readFromFile(filename, &seats);
                    editSeatNumber((Seat ***)seats, filename);

                    break;
                case 4:
                    // Step 5: Cancel reservation
                    readFromFile(filename, &seats);
                    cancelReservation((Seat ***)seats, filename);
                    break;
                case 5:
                    // Step 6: Display list of passengers
                    clearScreen();
                    readFromFile(filename, &seats);
                    showFileContent(filename);
                    break;
                case 6:
                    // Step 7: Exit
                    clearScreen();
                    printf("\n\t\tTHIS PROGRAM WAS CREATED BY: WILLIE M. BONAVENTE\n");
                    printf("\t\t\t\tBSIT 1-5\n");
                    printf("\n\t\t\tTHE PROGRAM IS NOW EXITING.\t\t\n");
                    loadingScreen();
                    exit(1);
                    break;
                default:
                    clearScreen();
                    printf("\n\t\t\tError! P4lease select a valid option.\t\t\n");
                    printf("\n");
                }

                printf("\n\tReturn to Main Menu (Press 'Y') >> ");
                scanf(" %c", &another);
                clearScreen();
            } while (another == 'Y' || another == 'y');
        }

        else
        {
            clearScreen();
            printf("\n");
            printf("\t\tInvalid password. Login failed.\n");
        }
    }

    // Program Existing.
    printf("\n\t\tTHIS PROGRAM WAS CREATED BY: WILLIE M. BONAVENTE\n");
    printf("\t\t\t\tBSIT 1-5\n");
    printf("\n\t\t\tTHE PROGRAM IS NOW EXITING.\t\t\n");
    loadingScreen();
    freeSeats(&seats);
    return 0;
}

void loadingScreen()
{
    int i;

    for (i = 5; i > 0; i--)
    {
        printf("\t\t\t\t%d...\n", i);
        sleep(1);
    }
    clearScreen();
}

void clearScreen()
{
#ifdef _WIN32
    system("cls");

#endif
}

void inputFilename(char *filename)
{
    printf("Enter the filename >> ");
    fgets(filename, MAX_FILENAME_LENGTH, stdin);
    filename[strcspn(filename, "\n")] = '\0'; // Remove trailing newline character
}

void showMenu()
{
    printf("\n\t\t\tMAIN MENU\t\t\n");
    printf("\n");
    printf("\t\t[1] Display the Available Seats\n");
    printf("\t\t[2] Add Passenger\n");
    printf("\t\t[3] Edit Seat Number\n");
    printf("\t\t[4] Cancel Reservation\n");
    printf("\t\t[5] Display the List of Passengers\n");
    printf("\t\t[6] EXIT\n");
}

// Function definitions
void initializeSeats(Seat ***seats)
{
    *seats = (Seat **)malloc(MAX_ROW * sizeof(Seat *));
    for (int i = 0; i < MAX_ROW; i++)
    {
        (*seats)[i] = (Seat *)malloc(MAX_COL * sizeof(Seat));
        for (int j = 0; j < MAX_COL; j++)
        {
            (*seats)[i][j].passenger.assigned = false;
        }
    }
}

void freeSeats(Seat ***seats)
{
    // Free dynamically allocated memory for seats
    for (int i = 0; i < MAX_ROW; i++)
    {
        free((*seats)[i]);
    }
    free(*seats);
    *seats = NULL;
}

bool isSeatValid(int row, char col)
{
    // Check if the given seat is valid
    // Return true if valid, false otherwise
    return row >= 1 && row <= MAX_ROW && col >= 'A' && col <= ('A' + MAX_COL - 1);
}

void assignSeat(Seat ***seats, const char *name, int age, const char *address, int row, char col)
{
    // Assign the seat to the passenger
    strcpy((*seats)[row - 1][col - 'A'].passenger.name, name);
    (*seats)[row - 1][col - 'A'].passenger.age = age;
    strcpy((*seats)[row - 1][col - 'A'].passenger.address, address);
    (*seats)[row - 1][col - 'A'].passenger.assigned = true;
}

void addPassenger(Seat ***seats, const char *filename)
{
    char name[MAX_NAME_LENGTH];
    int age;
    char address[MAX_ADDRESS_LENGTH];
    int row;
    char col;
    char another; // if the user wants to add another record until they terminate

    do
    {
        printf("Enter passenger name (or press C to cancel): ");
        if (scanf("%s", name) == 1)
        {
            if (name[0] == 'C' || name[0] == 'c')
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
            if (address[0] == 'C' || address[0] == 'c')
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
            if (isSeatValid(row, col) && !(*seats)[row - 1][col - 'A'].passenger.assigned)
            {
                assignSeat(seats, name, age, address, row, col);

                // Save the seat assignment to a file
                assignSeat(seats, name, age, address, row, col);
                printf("Seat assigned successfully.\n");
                appendToFile(filename, name, age, address, row, col);
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

void writeToFile(const char *filename, Seat ***seats)
{
    // Write the seat assignments to a file
    FILE *file = fopen(filename, "w");
    if (file == NULL)
    {
        printf("Error opening file for writing.\n");
        return;
    }

    for (int i = 0; i < MAX_ROW; i++)
    {
        for (int j = 0; j < MAX_COL; j++)
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

void readFromFile(const char *filename, Seat ***seats)
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
                if (isSeatValid(row, col))
                {
                    assignSeat(seats, name, age, address, row, col);
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
void displaySeats(const Seat **seats)
{
    // Display the current seat map
    clearScreen();

    int terminalWidth = 80;
    int headerWidth = strlen("Available Seat Map");
    int seatMapWidth = MAX_COL * 8 + 1;

    // Calculate the number of spaces needed to center the header.
    int paddingHeader = (terminalWidth - headerWidth) / 2;

    printf("\n\n");
    printf("\t\t       ---------------------------------\n");
    printf("%*s%s\n", paddingHeader, "", "Available Seat Map");
    printf("\t\t       ---------------------------------\n");

    // Calculate the number of spaces needed to center the seat map
    int paddingSeatMap = (terminalWidth - seatMapWidth) / 2;

    for (int i = 0; i < MAX_ROW; i++)
    {
        printf("%*s%d", paddingSeatMap, " ", i + 1);
        for (int j = 0; j < MAX_COL; j++)
        {
            if (seats[i][j].passenger.assigned)
            {
                printf("      X ");
            }
            else
            {
                printf("      %c ", 'A' + j);
            }
        }
        printf("\n%*s---------------------------------\n", paddingSeatMap, "");
    }
    printf("\n");
}

void showFileContent(const char *filename)
{
    int count = 0;
    printf("\n\t\t\tList of Passengers\t\t\n");
    printf("\n");
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
            printf("\t%d. %-15s%-15d%-17s%d%c\n", count, name, age, address, row, col);
        }
    }

    fclose(file);

    if (count == 0)
    {
        printf("No passenger records found.\n");
    }
}

void clearFile(const char *filename)
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

void appendToFile(const char *filename, const char *name, int age, const char *address, int row, char col)
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

void modifySeatAssignment(Seat ***seats)
{
    // Modify the seat assignment
    printf("Enter the row and column of the seat to modify (e.g., 1A): ");
    int row;
    char col;
    scanf("%d %c", &row, &col);

    if (isSeatValid(row, col))
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

            assignSeat(seats, newName, newAge, newAddress, row, col);
            printf("Seat modified successfully.\n");

            printf("Enter the filename to save seat assignments: ");
            char filename[MAX_FILENAME_LENGTH];
            scanf(" %[^\n]", filename);
            writeToFile(filename, (Seat ***)seats);
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

bool userLogin()
{
    char password[20];
    printf("Enter the password: ");
    scanf("%s", password);

    // Check if the entered password is correct
    if (strcmp(password, "password123") == 0)
    {
        printf("\n");
        printf("\t\t\tLOGIN SUCCESSFUL!\t\t\n");
        return true;
    }
    else
        return false;
}

void editSeatNumber(Seat ***seats, const char *filename)
{
    displaySeats((const Seat **)seats);

    int fromRow;
    char fromCol;
    int toRow;
    char toCol;
    char cancel;

    while (true)
    {
        printf("Enter the current seat number (row column) or press C to cancel: ");
        if (scanf("%d %c", &fromRow, &fromCol) == 2)
        {
            printf("Enter the new seat number (row column): ");
            scanf("%d %c", &toRow, &toCol);

            if (isSeatValid(fromRow, fromCol) && isSeatValid(toRow, toCol) &&
                (*seats)[fromRow - 1][fromCol - 'A'].passenger.assigned &&
                !(*seats)[toRow - 1][toCol - 'A'].passenger.assigned)
            {
                modifySeat(seats, fromRow, fromCol, toRow, toCol);
                printf("Seat number modified successfully.\n");
                writeToFile(filename, (Seat ***)seats);
            }
            else
            {
                printf("Invalid seat numbers or seat assignment.\n");
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
                printf("Invalid input. Please try again.\n");
            }
        }
    }
}

void modifySeat(Seat ***seats, int fromRow, char fromCol, int toRow, char toCol)
{
    (*seats)[toRow - 1][toCol - 'A'].passenger = (*seats)[fromRow - 1][fromCol - 'A'].passenger;
    (*seats)[fromRow - 1][fromCol - 'A'].passenger.assigned = false;
    (*seats)[fromRow - 1][fromCol - 'A'].passenger.name[0] = '\0';
}

void cancelReservation(Seat ***seats, const char *filename)
{
    int row;
    char col;
    char cancel;
    clearScreen();

    do
    {
        showFileContent(filename);

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
                clearScreen();
                printf("Invalid input. Please enter a valid seat number or 'C' to cancel.\n");
                continue; // Restart the loop to prompt for a valid seat number
            }
        }

        if (isSeatValid(row, col) && (*seats)[row - 1][col - 'A'].passenger.assigned)
        {
            (*seats)[row - 1][col - 'A'].passenger.assigned = false;
            (*seats)[row - 1][col - 'A'].passenger.name[0] = '\0';

            // Save the updated seat assignment to the file
            printf("Reservation canceled successfully.\n");
            writeToFile(filename, (Seat ***)seats);
        }
        else
        {
            clearScreen();
            printf("\n\t\tInvalid seat or seat is not assigned.\n");
        }

    } while (1); // Continue the loop until a valid seat is canceled or the user cancels the cancellation process with 'C'

    clearScreen();
}
