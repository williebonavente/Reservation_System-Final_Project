#include <stdio.h>
#include <stdbool.h>
#include <string.h>

// Constants
#define MAX_ROW 5
#define MAX_COL 4
#define MAX_NAME_LENGTH 50
#define MAX_FILENAME_LENGTH 100

// Struct definitions
typedef struct
{
    char name[MAX_NAME_LENGTH];
    bool assigned;
} Passenger;

typedef struct
{
    Passenger passenger;
} Seat;

// Function declarations
void initializeSeats(Seat ***seats);
void freeSeats(Seat ***seats);
bool isSeatValid(int row, char col);
void assignSeat(Seat ***seats, int row, char col, const char *name);
void displaySeats(const Seat ***seats);
void writeToFile(const char *filename, const Seat ***seats);
void readFromFile(const char *filename, Seat ***seats);
void showFileContent(const char *filename);
void clearFile(const char *filename);
void appendToFile(const char *filename, int row, char col, const char *name);
void modifySeatAssignment(Seat ***seats);
bool userLogin();
void createPassword(char password[]);
void forgotPassword(char password[]);
bool additionalAuthentication();

// Main function
int main()
{
    Seat **seats;
    initializeSeats(&seats);

    // Step 1: User login with correct password
    bool loggedIn = userLogin();

    // continue with the remaining steps if logged in successfully

    if (loggedIn)
    {
        // Step 2: Display available seats
        displaySeats(&seats);

        // Step 3: Add passengers

        // Step 4: Edit seat number

        // Step 5: Cancel reservation

        // Step 6: Display list of passengers

        // Step 7: Exit
    }
    freeSeats(&seats);
    return 0;
}

// Function definitions
void initializeSeats(Seat ***seats)
{
    // Initialize seats with default values
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

void assignSeat(Seat ***seats, int row, char col, const char *name)
{
    // Assign the seat to the passenger
    (*seats)[row - 1][col - 'A'].passenger.assigned = true;
    strcpy((*seats)[row - 1][col - 'A'].passenger.name, name);
}

void displaySeats(const Seat ***seats)
{
    // Display the current seat map
    printf("Available Seats:\n");
    printf("   ");
    for (int j = 0; j < MAX_COL; j++)
    {
        printf(" %c ", 'A' + j);
    }
    printf("\n");
    for (int i = 0; i < MAX_ROW; i++)
    {
        printf("%d  ", i + 1);
        for (int j = 0; j < MAX_COL; j++)
        {
            if ((*seats)[i][j].passenger.assigned)
                printf(" X ");
            else
                printf(" - ");
        }
        printf("\n");
    }
}

void writeToFile(const char *filename, const Seat ***seats)
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
                fprintf(file, "%d%c\t\t%s\n", i + 1, 'A' + j, (*seats)[i][j].passenger.name);
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

    char line[100];
    while (fgets(line, sizeof(line), file))
    {
        int row;
        char col;
        char name[MAX_NAME_LENGTH];

        if (sscanf(line, "%d%c %[^\n]", &row, &col, name) == 3)
        {
            if (isSeatValid(row, col))
            {
                assignSeat(seats, row, col, name);
            }
        }
    }

    fclose(file);
}

void showFileContent(const char *filename)
{
    // Display the content of the file
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Error opening file for reading.\n");
        return;
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

void appendToFile(const char *filename, int row, char col, const char *name)
{
    // Append seat assignment to the file
    FILE *file = fopen(filename, "w");
    if (file == NULL)
    {
        printf("Error opening file for writing.\n");
        return;
    }

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
            assignSeat(seats, row, col, newName);
            printf("Seat modified successfully.\n");

            printf("Enter the filename to save seat assignments: ");
            char filename[MAX_FILENAME_LENGTH];
            scanf(" %[^\n]", filename);
            writeToFile(filename, (const Seat ***)seats);
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
        printf("Login successful!");
        return true;
    }
    else
    {
        printf("Invalid password. Login failed.\n");
        return false;
    }
}