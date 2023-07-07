#include <stdio.h>
#include <stdbool.h>
#include <string.h>

// Constants
#define MAX_ROW 5
#define MAX_COL 4
#define MAX_NAME_LENGTH 50
#define MAX_FILENAME_LENGTH 100

// Struct definitions
typedef struct {
    char name[MAX_NAME_LENGTH];
    bool assigned;
} Passenger;

typedef struct {
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
void createPassword(char password[]);
bool userLogin();
void forgotPassword(char password[]);
bool additionalAuthentication()

// Main function
int main() {
    Seat **seats;
    initializeSeats(&seats);

    // Step 1: User login with correct password

    // Step 2: Display available seats

    // Step 3: Add passengers

    // Step 4: Edit seat number

    // Step 5: Cancel reservation

    // Step 6: Display list of passengers

    // Step 7: Exit

    freeSeats(&seats);
    return 0;
}

// Function definitions
void initializeSeats(Seat ***seats) {
    // Initialize seats with default values
}

void freeSeats(Seat ***seats) {
    // Free dynamically allocated memory for seats
}

bool isSeatValid(int row, char col) {
    // Check if the given seat is valid
    // Return true if valid, false otherwise
}

void assignSeat(Seat ***seats, int row, char col, const char *name) {
    // Assign the seat to the passenger
}

void displaySeats(const Seat ***seats) {
    // Display the current seat map
}

void writeToFile(const char *filename, const Seat ***seats) {
    // Write the seat assignments to a file
}

void readFromFile(const char *filename, Seat ***seats) {
    // Read seat assignments from a file
}

void showFileContent(const char *filename) {
    // Display the content of the file
}

void clearFile(const char *filename) {
    // Clear the content of the file
}

void appendToFile(const char *filename, int row, char col, const char *name) {
    // Append seat assignment to the file
}

void modifySeatAssignment(Seat ***seats) {
    // Modify the seat assignment
}

bool userLogin()
{
    char password[20];
    printf("Enter the password: "); 
    scanf("%s", password);

    // Check if the entered password is correct
    if (strcmp(password, ""))
    {
        /* code */
    }
    
}