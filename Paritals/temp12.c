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
                    printf("\n\t\tTHIS PROGRAM WAS CREATED BY: WILLIE M. BONAVENTE\n");
                    printf("\t\t\t\tBSIT 1-5\n");
                    printf("\n\t\t\tTHE PROGRAM IS NOW EXITING.\t\t\n");
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

    // Program Existing.
    printf("\n\t\tTHIS PROGRAM WAS CREATED BY: WILLIE M. BONAVENTE\n");
    printf("\t\t\t\tBSIT 1-5\n");
    printf("\n\t\t\tTHE PROGRAM IS NOW EXITING.\t\t\n");
    loading_screen();
    free_sts(&seats);
    return 0;

    return 0;
}

void disp_menu()
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

void clearScn()
{
#ifdef _WIN32
    system("cls");

#endif
}
void loading_screen()
{
    int i;

    for (i = 3; i > 0; i--)
    {
        printf("\t\t\t\t%d...\n", i);
        sleep(1);
    }

    clearScn();
}

void inp_filename(char *filename)
{
    printf("Enter the filename >> ");
    fgets(filename, MAX_FILENAME_LENGTH, stdin);
    filename[strcspn(filename, "\n")] = '\0'; // Remove trailing newline character
}

void init_sts(Seat ***seats)
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
void free_sts(Seat ***seats)

{
    // Free dynamically allocated memory for seats
    for (int i = 0; i < MAX_ROW; i++)
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
            if (validity(row, col) && !(*seats)[row - 1][col - 'A'].passenger.assigned)
            {
                assigning(seats, name, age, address, row, col);

                // Save the seat assignment to a file
                clearScn();
                assigning(seats, name, age, address, row, col);
                printf("Seat assigned successfully.\n");
                printf("Name: %s\n", name);
                printf("Age: %d\n", age);
                printf("Address: %s\n", address);
                printf("Seat: %d%c\n", row, col);
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

void showing(const char *filename)
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