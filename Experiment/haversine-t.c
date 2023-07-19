#include <stdio.h>
#include <math.h>
#include <stdbool.h>

#define PI 3.14159265358979323846
#define EARTH_RADIUS_KM 6371.0
#define DEG_TO_RAD(deg) ((deg) * PI / 180.0)

// Function to validate latitude and longitude input
bool isValidCoordinate(float latitude, float longitude) {
    return latitude >= -90.0 && latitude <= 90.0 && longitude >= -180.0 && longitude <= 180.0;
}

int main(void)
{
    float latitude1, latitude2;
    float longitude1, longitude2;

    // Get input for latitude1 until a valid value is entered
    do {
        printf("Enter the latitude 1 (-90 to 90 degrees): ");
        if (scanf("%f", &latitude1) != 1) {
            printf("Invalid input. Please enter a valid floating-point number.\n");
            fflush(stdin); // Clear the input buffer
        }
    } while (!isValidCoordinate(latitude1, longitude1));

    // Get input for longitude1 until a valid value is entered
    do {
        printf("Enter the longitude 1 (-180 to 180 degrees): ");
        if (scanf("%f", &longitude1) != 1) {
            printf("Invalid input. Please enter a valid floating-point number.\n");
            fflush(stdin); // Clear the input buffer
        }
    } while (!isValidCoordinate(latitude1, longitude1));

    // Get input for latitude2 until a valid value is entered
    do {
        printf("Enter the latitude 2 (-90 to 90 degrees): ");
        if (scanf("%f", &latitude2) != 1) {
            printf("Invalid input. Please enter a valid floating-point number.\n");
            fflush(stdin); // Clear the input buffer
        }
    } while (!isValidCoordinate(latitude2, longitude2));

    // Get input for longitude2 until a valid value is entered
    do {
        printf("Enter the longitude 2 (-180 to 180 degrees): ");
        if (scanf("%f", &longitude2) != 1) {
            printf("Invalid input. Please enter a valid floating-point number.\n");
            fflush(stdin); // Clear the input buffer
        }
    } while (!isValidCoordinate(latitude2, longitude2));

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
