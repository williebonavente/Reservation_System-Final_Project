#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <conio.h>
// Constants
#define MAX_ROW 5
#define MAX_COL 4
#define MAX_FILENAME_LENGTH 25
#define MAX_NAME_LENGTH 100
#define MAX_ADDRESS_LENGTH 100
#define MAX_PASSWORD_LENGTH 50
#define MAX_SECURITY_QUESTION_LENGTH 250

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
void initializeSeats(Seat seats[MAX_ROW][MAX_COL]);
void clearScreen();
// Step 2 / Case 2
void addPassenger(Seat seats[MAX_ROW][MAX_COL], const char *filename);
bool isSeatValid(int row, char col);
void assignSeat(Seat seats[MAX_ROW][MAX_COL], const char *name, int age, const char *address, int row, char col);
void displaySeats(const Seat seats[MAX_ROW][MAX_COL]);
void writeToFile(const char *filename, const Seat seats[MAX_ROW][MAX_COL]);
void readFromFile(const char *filename, Seat seats[MAX_ROW][MAX_COL]);

// Step 3  / Case 3
void editSeatNumber(Seat seats[MAX_ROW][MAX_COL], const char *filename);
void modifySeat(Seat seats[MAX_ROW][MAX_COL], int fromRow, char fromCol, int toRow, char toCol);

// Step 4 / Case 4
void cancelReservation(Seat seats[MAX_ROW][MAX_COL], const char *filename);

// Menu File Functions - 1
void showFileContent(const char *filename);
void clearFile(const char *filename);
void appendToFile(const char *filename, const char *name, int age, const char *address, int row, char col);
// todo: Authentication - Layers of Security - FUNCTIONS
bool userLogin();
void createPassword(char password[]);
void savePasswordToFile(const char *filename, const char *password);
bool checkPasswordInDatabase(const char *filename, const char *password);
void forgotPassword(char password[]);
void saveUserToDatabase(const char *filename, const char *username, const char *password, const char *securityQuestion, const char *securityAnswer);
void censorPassword(char *password);
void getPassword(char *password);
// void deleteRecord(const char *filename, int row, char col);
// void sortRecordsByField(const char *filename, const char *field, const char *order);
// int compareByName(const void *a, const void *b);
// int compareByAge(const void *a, const void *b);
// int compareByNameDesc(const void *a, const void *b);
// int compareByAgeDesc(const void *a, const void *b);

// Main function - Driver Function
int main()
{
    Seat seats[MAX_ROW][MAX_COL];
    initializeSeats(seats);

    int choice;   // choice by the user on the menu.
    char another; //  if the user wants to continue.

    // get the filename from the user
    char filename[MAX_FILENAME_LENGTH];

    inputFilename(filename);

    bool loggedIn = userLogin();
    // Step 0: User login with correct password

    // continue with the remaining steps if logged in successfully
    if (loggedIn)
    {
        printf("\n");
        printf("\t\t\tLOGIN SUCCESSFUL!\t\t\n");
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
                readFromFile(filename, seats);
                displaySeats(seats);
                break;
            case 2:
                // Step 3: Add passengers
                clearScreen();
                addPassenger(seats, filename);
                break;
            case 3:
                // Step 4: Edit seat number
                readFromFile(filename, seats);
                editSeatNumber(seats, filename);

                break;
            case 4:
                // Step 5: Cancel reservation
                readFromFile(filename, seats);
                cancelReservation(seats, filename);
                break;
            case 5:
                // Step 6: Display list of passengers
                showFileContent(filename);
                break;
            case 6:
                // Step 7: Exit
                clearScreen();
                printf("\n\t\t\tTHE PROGRAM IS NOW EXITING.\t\t\n");
                loadingScreen();
                return 0;
            default:
                clearScreen();
                printf("\n\t\t\tError! Please select a valid option.\t\t\n");
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
        printf("\t\tLogin failed.\n");
    }

    // Program Exiting.
    printf("\n\t\t\tProgram Exiting in\n");
    loadingScreen();
    return 0;
}

void loadingScreen()
{
    int i;

    for (i = 3; i > 0; i--)
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
    filename[strcspn(filename, "\n")] = '\0'; // Remove trailing newline
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
void initializeSeats(Seat seats[MAX_ROW][MAX_COL])
{
    // Initialize seats with default values
    for (int i = 0; i < MAX_ROW; i++)
    {
        for (int j = 0; j < MAX_COL; j++)
        {
            seats[i][j].passenger.assigned = false;
        }
    }
}

bool isSeatValid(int row, char col)
{
    // Check if the given seat is valid
    // Return true if valid, false otherwise
    return row >= 1 && row <= MAX_ROW && col >= 'A' && col <= ('A' + MAX_COL - 1);
}

void assignSeat(Seat seats[MAX_ROW][MAX_COL], const char *name, int age, const char *address, int row, char col)
{
    // Assign the seat to the passenger
    strcpy(seats[row - 1][col - 'A'].passenger.name, name);
    seats[row - 1][col - 'A'].passenger.age = age;
    strcpy(seats[row - 1][col - 'A'].passenger.address, address);
    seats[row - 1][col - 'A'].passenger.assigned = true;
}

void addPassenger(Seat seats[MAX_ROW][MAX_COL], const char *filename)
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
            if (isSeatValid(row, col) && !(seats)[row - 1][col - 'A'].passenger.assigned)
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

void writeToFile(const char *filename, const Seat seats[MAX_ROW][MAX_COL])
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
            if ((seats)[i][j].passenger.assigned)
            {
                fprintf(file, "%s\t%d\t%s\t%d%c\n", (seats)[i][j].passenger.name, (seats)[i][j].passenger.age,
                        (seats)[i][j].passenger.address, i + 1, 'A' + j);
            }
        }
    }

    fclose(file);
}

void readFromFile(const char *filename, Seat seats[MAX_ROW][MAX_COL])
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
                    strcpy((seats)[row - 1][col - 'A'].passenger.name, name);
                    (seats)[row - 1][col - 'A'].passenger.age = age;
                    strcpy((seats)[row - 1][col - 'A'].passenger.address, address);
                }
            }
        }

        fclose(file);
    }
}

void displaySeats(const Seat seats[MAX_ROW][MAX_COL])
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
    clearScreen();
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

void editSeatNumber(Seat seats[MAX_ROW][MAX_COL], const char *filename)
{
    displaySeats(seats);

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
                (seats)[fromRow - 1][fromCol - 'A'].passenger.assigned &&
                !(seats)[toRow - 1][toCol - 'A'].passenger.assigned)
            {
                modifySeat(seats, fromRow, fromCol, toRow, toCol);
                printf("Seat number modified successfully.\n");
                writeToFile(filename, seats);
                return; // Exit the function after modifying the seat
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

void cancelReservation(Seat seats[MAX_ROW][MAX_COL], const char *filename)
{
    int row;
    char col;
    char cancel;

    do
    {
        displaySeats(seats);

        printf("Enter the seat to cancel (row column) or press C to cancel: ");
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
                printf("Invalid input. Please enter a valid seat number or 'C' to cancel.\n");
                continue; // Restart the loop to prompt for a valid seat number
            }
        }

        if (isSeatValid(row, col) && (seats)[row - 1][col - 'A'].passenger.assigned)
        {
            (seats)[row - 1][col - 'A'].passenger.assigned = false;
            (seats)[row - 1][col - 'A'].passenger.name[0] = '\0';

            // Save the updated seat assignment to the file
            writeToFile(filename, seats);

            printf("Reservation canceled successfully.\n");
        }
        else
        {
            printf("Invalid seat or seat is not assigned.\n");
        }

    } while (1); // Continue the loop until a valid seat is canceled or the user cancels the cancellation process with 'C'
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

void modifySeat(Seat seats[MAX_ROW][MAX_COL], int fromRow, char fromCol, int toRow, char toCol)
{
    (seats)[toRow - 1][toCol - 'A'].passenger = (seats)[fromRow - 1][fromCol - 'A'].passenger;
    (seats)[fromRow - 1][fromCol - 'A'].passenger.assigned = false;
    (seats)[fromRow - 1][fromCol - 'A'].passenger.name[0] = '\0';
}

bool userLogin()
{
    char password[MAX_PASSWORD_LENGTH];
    char choice;

    printf("Do you have an existing password? (Y/N): ");
    scanf(" %c", &choice);

    if (choice == 'Y' || choice == 'y')
    {
        // Retrieve the existing password from the database and prompt the user for password input
        printf("Enter your existing password: ");
        getPassword(password);

        // Check if the provided password matches the one in the database
        if (checkPasswordInDatabase("database.bin", password))
        {
            return true; // Login successful
        }
        else
        {
            // If the password does not match, ask the user if they want to reset it.
            printf("Incorrect password. Do you want to reset your password? (Y/N): ");
            scanf(" %c", &choice);

            if (choice == 'Y' || choice == 'y')
            {
                // Call the function to reset the password
                forgotPassword(password);

                // Password has been reset, return true for successful login
                return true;
            }
            else
            {
                // Password is incorrect, and the user chose not to reset it.
                return false;
            }
        }
    }
    else
    {
        // Create a new password for the user
        createPassword(password);

        // Save the newly created password to the database
        savePasswordToFile("database.bin", password);

        // Indicate successful login after creating the password
        return true;
    }
}

void createPassword(char password[])
{
    bool validPassword = false;

    while (!validPassword)
    {
        printf("Enter a new password (up to %d characters): ", MAX_PASSWORD_LENGTH - 1);
        scanf("%s", password);

        // Check password length
        if (strlen(password) >= 8 && strlen(password) <= MAX_PASSWORD_LENGTH - 1)
        {
            // Check for password complexity (at least one uppercase letter and one digit)
            bool hasUppercase = false;
            bool hasDigit = false;

            for (size_t i = 0; i < strlen(password); i++)
            {
                if (password[i] >= 'A' && password[i] <= 'Z')
                    hasUppercase = true;
                else if (password[i] >= '0' && password[i] <= '9')
                    hasDigit = true;
            }

            if (hasUppercase && hasDigit)
                validPassword = true;
            else
                printf("Password must contain at least one uppercase letter and one digit.\n");
        }
        else
        {
            printf("Password must be between 8 and %d characters.\n", MAX_PASSWORD_LENGTH - 1);
        }

        // Clear the input buffer to avoid issues with consecutive inputs
        while (getchar() != '\n')
            continue;
    }
}

void savePasswordToFile(const char *filename, const char *password)
{
    FILE *file = fopen(filename, "wb");
    if (file == NULL)
    {
        printf("Error opening file for writing.\n");
        return;
    }

    // Write the password to the file in binary format
    fwrite(password, sizeof(char), strlen(password), file);

    fclose(file);
}

bool checkPasswordInDatabase(const char *filename, const char *password)
{
    FILE *file = fopen(filename, "rb");
    if (file == NULL)
    {
        printf("Error opening file for reading.\n");
        return false;
    }

    // Read the existing password from file
    char existingPassword[MAX_PASSWORD_LENGTH];
    size_t bytesRead = fread(existingPassword, sizeof(char), MAX_PASSWORD_LENGTH - 1, file);
    existingPassword[bytesRead] = '\0';

    fclose(file);

    // Check if the provided password matches the one in database
    return strcmp(existingPassword, password) == 0;
}

void saveUserToDatabase(const char *filename, const char *username, const char *password, const char *securityQuestion, const char *securityAnswer)
{
    FILE *file = fopen(filename, "a");
    if (file == NULL)
    {
        printf("Error opening database file for writing.\n");
        exit(1);
    }

    fprintf(file, "%s:%s:%s:%s\n", username, password, securityQuestion, securityAnswer);
    fclose(file);
}

void forgotPassword(char password[])
{
    char username[MAX_PASSWORD_LENGTH];
    char securityAnswer[MAX_PASSWORD_LENGTH];
    char newPassword[MAX_PASSWORD_LENGTH];

    printf("Enter your username: ");
    scanf("%s", username);

    // In a real-world scenario, you would fetch the user's information from the database
    // and retrieve their stored security question and answer.
    // For demonstration, we are assuming a known security answer.

    printf("Answer the security question: Who is the national traitor of the Philippines?\n");
    scanf("%s", securityAnswer);

    // In a real-world scenario, you would compare the hashed/encrypted security answer.
    // For demonstration purposes, we are using a plain text answer.

    if (strcmp(securityAnswer, "answer123") == 0)
    {
        // Security answer is correct. Prompt the user to enter a new password.
        createPassword(newPassword);

        // Save the new password to the database
        saveUserToDatabase("user_database.txt", username, newPassword, "Who is the national traitor of the Philippines?", "answer123");

        // Update the provided password parameter with the new password
        strcpy(password, newPassword);

        printf("Password reset successful. Your new password is set.\n");
    }
    else
    {
        printf("Incorrect security answer. Password reset failed.\n");
        exit(1);
    }
}

void censorPassword(char *password)
{
    int i = 0;
    while (password[i] != '\0')
    {
        password[i] = 'o';
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
            printf("\b \b"); // Erase the character from the console
        }
        else if (ch != '\b' && i < MAX_PASSWORD_LENGTH - 1)
        {
            password[i] = ch;
            i++;
            printf("o"); // Print asterisk to the console to censor the password
        }
    }

    password[i] = '\0';
    printf("\n");
}
