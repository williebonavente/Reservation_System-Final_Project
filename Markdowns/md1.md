# Seat Reservation System in C

This program implements a seat reservation system for a small airplane that can accommodate twenty passengers. The program allows users to login with a password and provides a menu with various options for managing seat reservations. The available features of the system include displaying available seats, adding passengers, editing seat numbers, canceling reservations, and displaying a list of passengers.

## Features

1. **Login**: The system requires user login with a password to access the main menu.
2. **Main Menu**: The main menu presents the user with different options to choose from.
3. **Display Available Seats**: This option displays the current seat availability in a grid format, where each seat is represented by a letter.
4. **Add Passenger**: Users can add passenger details, including name, age, and address. They can also choose a specific seat number to assign to the passenger.
5. **Edit Seat Number**: Users can modify the assigned seat number for a passenger.
6. **Cancel Reservation**: This option allows users to cancel a previously assigned seat reservation.
7. **Display List of Passengers**: Users can view a list of all passengers along with their assigned seats.
8. **Exit**: Choosing this option will exit the program.

## Usage

1. Upon running the program, the user is prompted to enter the number of persons to book and the seat assignment filename.
2. The initial seat map is displayed, showing the available seats.
3. Users are prompted to enter passenger details and select a seat number for each person.
4. After assigning the seats, the final seat map is displayed, reflecting the assigned seats.
5. The seat assignment is saved to the specified filename.
6. The main menu is presented to the user, allowing them to perform various operations.
7. Choosing "1. Show the content of the file" displays the content of the file containing the seat assignments.
8. Choosing "2. Clear all of the content of the file" clears the content of the file.
9. Choosing "3. Modify the content of the file" allows users to modify an assigned seat.
10. Choosing "4. Exit" terminates the program.

## File Handling

The program utilizes file handling operations to read from and write to a file containing the seat assignments. It provides options to show the content of the file, clear the content of the file, and modify the seat assignments. The file is specified by the user during program execution.

## Report Requirement

The program generates a report that lists all passengers along with their respective information and assigned seats.

``` Requirement
List of Passengers

Passenger Name  Age  Address     Seat No.
1. Matthew       21   Manila      1A
2. Vernice       20   Makati      1B
3. Luke          20   Pasay       1C
4. Mark          19   Valenzuela  1D
5. Silas         21   Malabon     5A
```

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for more details.

## Note

This code is a revised version based on the provided code. It follows a clearer structure, uses meaningful variable names, and adheres to ANSI C conventions for improved readability and maintainability.
