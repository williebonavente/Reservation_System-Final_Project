# Airline Reservation System

## Overview

The Airline Reservation System is a C program that allows users to manage seat reservations on a flight. The program provides a menu-driven interface for various operations like displaying available seats, adding passengers, editing seat numbers, canceling reservations, displaying the list of passengers, and exiting the program. The program uses the Haversine algorithm to calculate the distance between two points on Earth and the Floyd-Warshall algorithm for finding the shortest paths between all pairs of vertices in a graph.

## Constants

- `MAX_ROW`: The maximum number of rows of seats in the aircraft.
- `MAX_COL`: The maximum number of columns of seats in the aircraft.
- `MAX_FILENAME_LENGTH`: The maximum length of the filename.
- `MAX_NAME_LENGTH`: The maximum length of the passenger's name.
- `MAX_ADDRESS_LENGTH`: The maximum length of the passenger's address.

## Struct Definitions

1. `Passenger`: Represents a passenger with the following attributes:
   - `name`: An array to store the passenger's name.
   - `age`: An integer to store the passenger's age.
   - `address`: An array to store the passenger's address.
   - `assigned`: A boolean flag to indicate if the seat is assigned to the passenger.

2. `Seat`: Represents a seat on the aircraft with the following attribute:
   - `passenger`: A `Passenger` struct to store passenger information.

## Function Definitions

### Option 1

1. `showMenu()`: Displays the main menu options.
2. `loadingScreen()`: Displays a loading screen with a countdown.
3. `inputFilename(char *filename)`: Takes user input to get the filename.
4. `initializeSeats(Seat ***seats)`: Initializes the seats array dynamically.
5. `freeSeats(Seat ***seats)`: Frees the dynamically allocated memory for seats.
6. `clearScreen()`: Clears the console screen.

### Step 2 / Case 2

1. `addPassenger(Seat ***seats, const char *filename)`: Adds a passenger by taking user input for name, age, address, and seat number.
2. `isSeatValid(int row, char col)`: Checks if the given seat is valid (within aircraft bounds).
3. `assignSeat(Seat ***seats, const char *name, int age, const char *address, int row, char col)`: Assigns the seat to a passenger.
4. `displaySeats(const Seat **seats)`: Displays the available seat map.
5. `writeToFile(const char *filename, Seat **seats)`: Writes seat assignments to a file.
6. `readFromFile(const char *filename, Seat ***seats)`: Reads seat assignments from a file.

### Step 3 / Case 3

1. `editSeatNumber(Seat ***seats, const char *filename)`: Edits the seat number for a passenger.
2. `modifySeat(Seat ***seats, int fromRow, char fromCol, int toRow, char toCol)`: Modifies the seat assignment.

### Step 4 / Case 4

1. `cancelReservation(Seat ***seats, const char *filename)`: Cancels a reservation by freeing the assigned seat.

### Menu File Functions - 1

1. `showFileContent(const char *filename)`: Shows the list of passengers from the file.
2. `clearFile(const char *filename)`: Clears the content of the file.
3. `appendToFile(const char *filename, const char *name, int age, const char *address, int row, char col)`: Appends seat assignment to the file.
4. `modifySeatAssignment(Seat ***seats)`: Modifies the seat assignment for a passenger.

### Authentication - Layers of Security - FUNCTIONS

1. `userLogin()`: Authenticates the user with a password.
2. `createPassword(char password[])`: Creates a password for authentication.
3. `forgotPassword(char password[])`: Helps the user recover a forgotten password.
4. `additionalAuthentication()`: Provides additional authentication (not implemented).

## Main Function - Driver Function

1. Initializes the `Seat` array with `initializeSeats`.
2. Gets the filename with `inputFilename`.
3. Authenticates the user with `userLogin`.
4. If the user is authenticated, proceeds with the main menu.
5. Shows the menu options with `showMenu`.
6. Executes the selected operation based on user input.
7. Continues until the user decides to exit the program.
8. After each operation, asks if the user wants to return to the main menu.
9. Exits the program when the user chooses to exit.
10. Frees the dynamically allocated memory for seats with `freeSeats`.
