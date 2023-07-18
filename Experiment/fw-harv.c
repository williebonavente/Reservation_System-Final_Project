#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

#define PI 3.14159265358979323846
#define EARTH_RADIUS_KM 6371.0
#define DEG_TO_RAD(deg) ((deg) * PI / 180.0)

// Define an array of valid latitudes and longitudes
const float validLatitudes[] = {-90.0, -60.0, -30.0, 0.0, 30.0, 60.0, 90.0};
const float validLongitudes[] = {-180.0, -120.0, -60.0, 0.0, 60.0, 120.0, 180.0};
const int numValidCoordinates = sizeof(validLatitudes) / sizeof(validLatitudes[0]);

// Function to calculate distance between two coordinates using the Haversine formula
double calculateDistance(float latitude1, float longitude1, float latitude2, float longitude2) {
    double deltaLatitude = DEG_TO_RAD(latitude2 - latitude1);
    double deltaLongitude = DEG_TO_RAD(longitude2 - longitude1);
    latitude1 = DEG_TO_RAD(latitude1);
    latitude2 = DEG_TO_RAD(latitude2);

    double term1 = pow(sin(deltaLatitude / 2), 2);
    double term2 = pow(sin(deltaLongitude / 2), 2) * cos(latitude1) * cos(latitude2);
    double term3 = sqrt(term1 + term2);
    double centralAngle = 2 * asin(term3);

    return EARTH_RADIUS_KM * centralAngle;
}

// Function to perform Floyd-Warshall algorithm to find shortest distances between all pairs of coordinates
void floydWarshall(double distances[numValidCoordinates][numValidCoordinates]) {
    for (int k = 0; k < numValidCoordinates; k++) {
        for (int i = 0; i < numValidCoordinates; i++) {
            for (int j = 0; j < numValidCoordinates; j++) {
                if (distances[i][k] + distances[k][j] < distances[i][j]) {
                    distances[i][j] = distances[i][k] + distances[k][j];
                }
            }
        }
    }
}

int main(void) {
    // Create a 2D array to store the distances between coordinates
    double distances[numValidCoordinates][numValidCoordinates];

    // Initialize the distances between all coordinates using the Haversine formula
    for (int i = 0; i < numValidCoordinates; i++) {
        for (int j = 0; j < numValidCoordinates; j++) {
            float lat1 = validLatitudes[i];
            float lon1 = validLongitudes[i];
            float lat2 = validLatitudes[j];
            float lon2 = validLongitudes[j];
            distances[i][j] = calculateDistance(lat1, lon1, lat2, lon2);
        }
    }

    // Perform the Floyd-Warshall algorithm to find shortest distances between all pairs
    floydWarshall(distances);

    // Display the resulting shortest distances between all pairs of coordinates
    printf("Shortest distances between all pairs of coordinates:\n");
    for (int i = 0; i < numValidCoordinates; i++) {
        for (int j = 0; j < numValidCoordinates; j++) {
            printf("%.2f km\t", distances[i][j]);
        }
        printf("\n");
    }

    return 0;
}
