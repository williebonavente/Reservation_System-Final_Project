# Reservation System in C

This is a seat reservation system implemented in C. It allows users to reserve seats in a small airplane, display available seats, add passengers, edit seat numbers, cancel reservations, and display the list of passengers.

## Features

The reservation system has the following features:

1. User Login: The system requires user login with a correct password to access the main menu.
2. Main Menu: After successful login, the system presents a main menu with the following options:
   - Display the Available Seats
   - Add Passenger
   - Edit Seat Number
   - Cancel Reservation
   - Display the List of Passengers
   - Exit
3. Displaying Available Seats: The system displays a seat map showing the available seats in the airplane. The seat map is represented as a grid, and each seat is identified by a row number and a letter.
4. Seat Reservation: Users can reserve seats by choosing a seat number and letter. When a seat is successfully reserved, the letter is replaced with an 'X' in the seat map.
5. Seat Occupation Check: If a user selects a seat that is already occupied, the system prompts the user with a message asking if they want to continue. If the user chooses to continue, they can select another seat. If not, the system returns to the main menu.
6. Passenger Information: When adding a passenger, the system asks for their name, age, and address.
7. Editing and Canceling Reservations: Users can edit or cancel their reserved seats.
8. List of Passengers: The system generates a report that lists all the passengers along with their information (name, age, address) and assigned seat numbers.

## Usage

To use the reservation system, follow these steps:

1. Login: Enter the correct password to access the main menu.
2. Main Menu: Select an option from the main menu based on your desired action.
   - Display the Available Seats: View the seat map showing available seats.
   - Add Passenger: Enter the passenger's information and reserve a seat.
   - Edit Seat Number: Modify the seat number for a passenger.
   - Cancel Reservation: Cancel a reserved seat.
   - Display the List of Passengers: View the list of passengers and their information.
   - Exit: Quit the reservation system.
3. Follow the prompts and enter the required information as requested by the system.

## Example Seat Map

The following example illustrates a seat map before and after reservations:

Before Reservations:

``` Example 1  
1     A    B    C    D  
2     A    B    C    D
3     A    B    C    D
4     A    B    C    D
```

After Reserving Seat 1A and 2B:

``` Example 2
1     X    B    C    D 
2     A    X    C    D 
3     A    B    C    D
4     A    B    C    D
```

## Example Report - List of Passengers

The system generates a report showing the list of passengers and their information, along with their assigned seat numbers:

``` Example 1
              List of Passengers

Passenger Name   Age    Address    Seat No.

1. Matthew      21      Manila      1A
2. Vernice      20      Makati      1B
3. Luke         20      Pasay       1C
4. Mark         19      Valenzuela  1D
5. Silas        21      Malabon     5A
```

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

## Contributors

- [WILLIE M. BONAVENTE](https://github.com/yourusername) - Initial implementation
