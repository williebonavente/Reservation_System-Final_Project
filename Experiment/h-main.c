// Include necessary libraries for reading Excel files and standard I/O
#include <stdio.h>
#include <stdlib.h>

// Define structures for storing latitude, longitude, and country name data
struct Location {
    double latitude;
    double longitude;
    char country[100];
};

// Function to read the Excel file and store latitude, longitude, and country data
void readExcelData(const char* filename, struct Location* locations, int numLocations);

// Function to calculate distance using Haversine formula
double haversineDistance(double lat1, double lon1, double lat2, double lon2);

int main() {
    // Load Excel data into the locations array
    struct Location locations[100]; // Change 100 to match the number of rows in your Excel file
    int numLocations = 0;

    // Call readExcelData function to read the data from Excel
    readExcelData("Datas/data.xlsx", locations, numLocations);

    // Get user input for "From" and "Destination" coordinates
    double latFrom, lonFrom, latDest, lonDest;
    printf("Enter From Latitude: ");
    scanf("%lf", &latFrom);
    printf("Enter From Longitude: ");
    scanf("%lf", &lonFrom);
    printf("Enter Destination Latitude: ");
    scanf("%lf", &latDest);
    printf("Enter Destination Longitude: ");
    scanf("%lf", &lonDest);

    // Calculate distance using Haversine formula
    double distance = haversineDistance(latFrom, lonFrom, latDest, lonDest);

    // Find corresponding country names based on latitude and longitude
    char fromCountry[100], destCountry[100];
    // Search the locations array for the corresponding country names

    // Output the results
    printf("From: %.2f, %.2f (%s)\n", latFrom, lonFrom, fromCountry);
    printf("Destination: %.2f, %.2f (%s)\n", latDest, lonDest, destCountry);
    printf("Distance: %.2f km\n", distance);

    return 0;
}

void readExcelData(const char* filename, struct Location* locations, int numLocations) {
    // Implement this function using the chosen library to read Excel files
    // Open the Excel file, read data, and populate the locations array
}

double haversineDistance(double lat1, double lon1, double lat2, double lon2) {
    // Implement the Haversine formula here
    // This function should calculate and return the distance between two points
}

