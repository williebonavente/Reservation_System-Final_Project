# Final Project Requirement

## Reservation System in `C`

Develop a seat reservation system in C with the following features:

**a.** Consider a small airplane that can accommodate twenty passengers.

**b.** The system will ask for the user login and with the correct password.

**c.** If the password is correct the system will go to the main menu.

``` Sample Mapping

        Main Menu
    1. Display the Available Seat
    2. Add Passenger
    3. Edit Seat Number
    4. Cancel Reservation
    5. Display the List of Passengers
    6. Exit

```

**d.** Display the Available Seat

|      |      |      |      |     |
| ---- | ---- | ---- | ---- | --- |
| 1    | A    | B    | C    | D   |
|      |      |      |      |     |
| 2    | A    | B    | C    | D   |
| 3    | A    | B    | C    | D   |
|      |      |      |      |     |
| 4    | A    | B    | C    | D   |
|      |      |      |      |     |
| 5    |  A   | B    |  C   | D   |
|      |      |      |      |     |  
| ---- | ---- | ---- | ---- | --- |

**e.** sign a number and a letter. If the reserved successfully, `X` mark will replace the letter as shown below.

|      |      |      |      |     |
| ---- | ---- | ---- | ---- | --- |
| 1    | X    | B    | C    | D   |
|      |      |      |      |     |
| 2    | X    | B    | C    | D   |
| 3    | X    | B    | C    | D   |
|      |      |      |      |     |
| 4    | X    | B    | C    | D   |
|      |      |      |      |     |
| 5    |  X   | B    |  C   | D   |
|      |      |      |      |     |  
| ---- | ---- | ---- | ---- | --- |

**f** If the user has selected a seat already occupied, the system will prompt the user the message `Seat already occupied, would you like to continue (Y/N)`.
If the yes the system will ask for another seat number, if no, the system will display main menu.

**g.** The system will ask the following information of the passenger.

1. Name
2. Age
3. Address

**h**. The user can edit or cancel the seat saved.

## Report Requirement

``` The expectation
                   List of Passengers
    
    Passenger Name   Age    Address    Seat No.
    
    1. Matthew      21      Manila      1A
    2. Vernice      20      Makati      1B
    3. Luke         20      Pasay       1C
    4. Mark         19      Valenzuela  1D
    5. Silas        21      Malabon     5A
```
