#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

#define PI 3.14159265358979323846
#define EARTH_RADIUS_KM 6371.0
#define DEG_TO_RAD(deg) ((deg) * PI / 180.0)

// Define an array of sorted valid latitudes and longitudes
const float validLatitudes[] = {-90.0, -60.0, -30.0, 0.0, 30.0, 60.0, 90.0};
const float validLongitudes[] = {-180.0, -120.0, -60.0, 0.0, 60.0, 120.0, 180.0};
const int numValidCoordinates = sizeof(validLatitudes) / sizeof(validLatitudes[0]);

// Function to perform binary search and find the nearest valid coordinate
float findNearestValidCoordinate(const float* sortedCoordinates, int numCoordinates, float targetCoordinate) {
    int low = 0;
    int high = numCoordinates - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        float midCoordinate = sortedCoordinates[mid];

        if (midCoordinate == targetCoordinate) {
            return midCoordinate; // Exact match found, return the valid coordinate
        } else if (midCoordinate < targetCoordinate) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    // If no exact match found, return the nearest valid coordinate
    if (low >= numCoordinates) {
        return sortedCoordinates[numCoordinates - 1];
    } else if (high < 0) {
        return sortedCoordinates[0];
    } else {
        // Find the nearest valid coordinate to the targetCoordinate
        float lowCoordinate = sortedCoordinates[low];
        float highCoordinate = sortedCoordinates[high];
        return (fabs(lowCoordinate - targetCoordinate) < fabs(highCoordinate - targetCoordinate))
                   ? lowCoordinate
                   : highCoordinate;
    }
}

int main(void) {
    float latitude1, latitude2;
    float longitude1, longitude2;

    // Get input for latitude1 and validate using binary search
    do {
        printf("Enter the latitude 1 (-90 to 90 degrees): ");
        if (scanf("%f", &latitude1) != 1) {
            printf("Invalid input. Please enter a valid floating-point number.\n");
            fflush(stdin); // Clear the input buffer
        }
        latitude1 = findNearestValidCoordinate(validLatitudes, numValidCoordinates, latitude1);
    } while (latitude1 != findNearestValidCoordinate(validLatitudes, numValidCoordinates, latitude1));

    // Get input for longitude1 and validate using binary search
    do {
        printf("Enter the longitude 1 (-180 to 180 degrees): ");
        if (scanf("%f", &longitude1) != 1) {
            printf("Invalid input. Please enter a valid floating-point number.\n");
            fflush(stdin); // Clear the input buffer
        }
        longitude1 = findNearestValidCoordinate(validLongitudes, numValidCoordinates, longitude1);
    } while (longitude1 != findNearestValidCoordinate(validLongitudes, numValidCoordinates, longitude1));

    // Get input for latitude2 and validate using binary search
    do {
        printf("Enter the latitude 2 (-90 to 90 degrees): ");
        if (scanf("%f", &latitude2) != 1) {
            printf("Invalid input. Please enter a valid floating-point number.\n");
            fflush(stdin); // Clear the input buffer
        }
        latitude2 = findNearestValidCoordinate(validLatitudes, numValidCoordinates, latitude2);
    } while (latitude2 != findNearestValidCoordinate(validLatitudes, numValidCoordinates, latitude2));

    // Get input for longitude2 and validate using binary search
    do {
        printf("Enter the longitude 2 (-180 to 180 degrees): ");
        if (scanf("%f", &longitude2) != 1) {
            printf("Invalid input. Please enter a valid floating-point number.\n");
            fflush(stdin); // Clear the input buffer
        }
        longitude2 = findNearestValidCoordinate(validLongitudes, numValidCoordinates, longitude2);
    } while (longitude2 != findNearestValidCoordinate(validLongitudes, numValidCoordinates, longitude2));

    // Convert degrees to radians for calculations
    double deltaLatitude = DEG_TO_RAD(latitude2 - latitude1);
    double deltaLongitude = DEG_TO_RAD(longitude2 - longitude1);
    latitude1 = DEG_TO_RAD(latitude1);
    latitude2 = DEG_TO_RAD(latitude2);

    // Calculate the haversine formula
    double term1 = pow(sin(deltaLatitude / 2), 2);
    double term2 = pow(sin(deltaLongitude / 2), 2) * cos(latitude1) * cos(latitude2);
    double term3 = sqrt(term1 + term2);
    double centralAngle = 2 * asin(term3);

    double distance = EARTH_RADIUS_KM * centralAngle;

    printf("The distance between the points is approximately: %f km\n", distance);

    return 0;
}
