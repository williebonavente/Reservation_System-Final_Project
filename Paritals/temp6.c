// Prototype testing.


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

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

void displaySeats(const Seat **seats);
void initializeSeats(Seat ***seats);
void freeSeats(Seat ***seats);
void readFromFile(const char *filename, Seat ***seats);
void inputFilename(char *filename);
void assignSeat(Seat ***seats, const char *name, int age, const char *address, int row, char col);

bool isSeatValid(int row, char col);

int main(void)
{
    Seat **seats;
    initializeSeats(&seats);

    char filename[MAX_FILENAME_LENGTH];
    inputFilename(filename);

    readFromFile(filename, &seats);
    displaySeats((const Seat **)seats);
     freeSeats(&seats);
    return 0;
}

void displaySeats(const Seat **seats)
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

void inputFilename(char *filename)
{
    printf("Enter the filename >> ");
    fgets(filename, MAX_FILENAME_LENGTH, stdin);
    filename[strcspn(filename, "\n")] = '\0'; // Remove trailing newline character
}

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