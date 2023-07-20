# Flow of the Program

The program is designed to manage a passenger reservation system for a seating arrangement with multiple rows and columns. The flow of the program revolves around providing various functionalities to the user through a user-friendly interface. Here's a detailed explanation of the flow:

1. **showMenu**: This function displays the main menu options to the user.

2. **loadingScreen**: This function displays a loading screen or splash screen when the program starts.

3. **inputFilename**: This function takes a pointer to a character array as input and prompts the user to enter a filename.

4. **initializeSeats**: This function initializes all seats in the `seats` array to be unassigned.

5. **clearScreen**: This function clears the terminal/console screen.

6. **addPassenger**: This function allows the user to add a new passenger to a specific seat. It prompts the user to enter the passenger's name, age, address, and the desired seat (row and column).

7. **isSeatValid**: This function checks if a given seat (row and column) is valid within the specified range of rows and columns.

8. **assignSeat**: This function assigns a passenger to a specific seat in the `seats` array.

9. **displaySeats**: This function displays the current seating arrangement with assigned passenger details.

10. **writeToFile**: This function writes the passenger data from the `seats` array to a file specified by the filename.

11. **readFromFile**: This function reads passenger data from a file specified by the filename and populates the `seats` array.

12. **editSeatNumber**: This function allows the user to edit the seat number (row and column) of an existing passenger.

13. **modifySeat**: This function modifies the seat number of an existing passenger in the `seats` array.

14. **cancelReservation**: This function allows the user to cancel the reservation of an existing passenger.

15. **showFileContent**: This function displays the content of the file containing passenger records.

16. **clearFile**: This function clears the content of the file specified by the filename.

17. **appendToFile**: This function appends passenger data to the file specified by the filename.

18. **userLogin**: This function handles user authentication by prompting for a username and password.

19. **createPassword**: This function generates a password for the user during account creation.

20. **savePasswordToFile**: This function saves the user's password to the database (file).

21. **checkPasswordInDatabase**: This function checks if a given password matches the one saved in the database.

22. **forgotPassword**: This function allows the user to reset their password in case they forgot it.

23. **saveUserToDatabase**: This function saves a new user (username, password, security question, and answer) to the database.

24. **censorPassword**: This function masks the password characters when displayed on the screen.

25. **getPassword**: This function securely prompts the user to enter their password without showing it on the screen.

26. **deleteRecord**: This function allows the user to delete a passenger record by providing the passenger's name.

27. **compareByName**: This function is a comparison function for sorting by passenger name.

28. **compareByAgeAscending**: This function is a comparison function for sorting by passenger age in ascending order.

29. **compareByAgeDescending**: This function is a comparison function for sorting by passenger age in descending order.

30. **searchRecords**: This function allows the user to search for passenger records based on name, age, or address.

31. **customView**: This function provides a custom view of passenger records based on the user's choice (name only, age only, address only).

32. **sortByName**: This function sorts the passenger records in the `seats` array based on passenger names in ascending or descending order.

33. **sortByAge**: This function sorts the passenger records in the `seats` array based on passenger age in ascending or descending order.

34. **sortByAddress**: This function sorts the passenger records in the `seats` array based on passenger addresses in ascending or descending order.

35. **countAssignedRecords**: This function counts the number of assigned seats (i.e., occupied seats) in the `seats` array.

36. **sortMenu**: This function provides a menu to the user to choose the field and order for sorting passenger records.
