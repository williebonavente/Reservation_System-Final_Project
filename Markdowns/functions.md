# List of Functions

## Main function - Driver Function

The `main` function is the entry point of the program. It initializes the `seats` array, prompts for the filename, performs user login, and executes the main program loop based on user choices.

## Function Declarations

The function declarations are listed in this section. These functions are defined and used in the program for various tasks.

## Function Definitions

1. `loadingScreen()`: Displays a loading screen with a countdown before executing the main program.
2. `clearScreen()`: Clears the console screen.
3. `inputFilename(char *filename)`: Prompts the user to input the filename.
4. `showMenu()`: Displays the main menu options.
5. `initializeSeats(Seat ***seats)`: Initializes the `seats` array with default values.
6. `freeSeats(Seat ***seats)`: Frees the memory allocated for the `seats` array.
7. `isSeatValid(int row, char col)`: Checks if the given seat is valid.
8. `assignSeat(Seat ***seats, const char *name, int age, const char *address, int row, char col)`: Assigns a seat to a passenger.
9. `addPassenger(Seat ***seats, const char *filename)`: Adds a passenger by taking user input for name, age, address, and seat number.
10. `writeToFile(const char *filename, Seat **seats)`: Writes seat assignments to a file.
11. `readFromFile(const char *filename, Seat ***seats)`: Reads seat assignments from a file.
12. `displaySeats(const Seat **seats)`: Displays the available seats on the console.
13. `showFileContent(const char *filename)`: Displays the list of passengers from a file.
14. `clearFile(const char *filename)`: Clears the content of a file.
15. `appendToFile(const char *filename, const char *name, int age, const char *address, int row, char col)`: Appends seat assignments to a file.
16. `modifySeatAssignment(Seat ***seats)`: Modifies the seat assignment for a passenger.
17. `userLogin()`: Performs user login by checking the entered password.
18. `editSeatNumber(Seat ***seats, const char *filename)`: Edits the seat number of a passenger.
19. `modifySeat(Seat ***seats, int fromRow, char fromCol, int toRow, char toCol)`: Modifies the seat assignment from one seat to another.
20. `cancelReservation(Seat ***seats, const char *filename)`: Cancels the reservation for a seat.

## Supporting Functions

These are additional functions used in the program for various tasks:

- `loadingScreen()`: Displays a loading screen with a countdown.
- `clearScreen()`: Clears the console screen.
- `userLogin()`: Performs user login by checking the entered password.
- `showMenu()`: Displays the main menu options.
- `inputFilename(char *filename)`: Prompts the user to input the filename.

The program flow starts with the `main` function, which executes the main program loop based on user choices. The user is prompted to input the filename and login with the correct password. Then, the program displays the main menu and performs the corresponding actions based on the user's choice. The program continues executing the main loop until the user chooses to exit.
