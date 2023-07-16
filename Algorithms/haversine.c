#include <stdio.h>
#include <math.h>

#define PI 3.14159265358979323846
#define EARTH_RADIUS_KM 6371.0
#define DEG_TO_RAD(deg) ((deg) * PI / 180.0)

int main(void)
{
    float latitude1, latitude2;
    float longitude1, longitude2;

    printf("Enter the latitude 1: ");
    scanf("%f", &latitude1);
    printf("Enter the longitude 1: ");
    scanf("%f", &longitude1);
    printf("Enter the latitude 2: ");
    scanf("%f", &latitude2);
    printf("Enter the longitude 2: ");
    scanf("%f", &longitude2);

    double deltaLatitude = DEG_TO_RAD(latitude2 - latitude1);
    double deltaLongitude = DEG_TO_RAD(longitude2 - longitude1);
    latitude1 = DEG_TO_RAD(latitude1);
    latitude2 = DEG_TO_RAD(latitude2);

    double term1 = pow(sin(deltaLatitude / 2), 2);
    double term2 = pow(sin(deltaLongitude / 2), 2) * cos(latitude1) * cos(latitude2);
    double term3 = sqrt(term1 + term2);
    double centralAngle = 2 * asin(term3);

    double distance = EARTH_RADIUS_KM * centralAngle;

    printf("The distance between the points is approximately: %f km\n", distance);

    return 0;
}
