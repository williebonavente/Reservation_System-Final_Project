/*
Formula
d = 2r asin(sqrt(sin^2(x2 - x1)/2) + cos(x1) * cos(x2) * sin^2(y2 - y1)/2)
*/

#include <stdio.h>
#include <math.h>

#define const float M_PI 3.141592653
int main(void)
{
    float lat1, lat2;
    float lon2, lon1;
    double radius = 6371.0;

    printf("Enter the x1: ");
    scanf("%f", &lat1);
    printf("Enter the y1: ");
    scanf("%f", &lon1);
    printf("Enter the x2: ");
    scanf("%f", &lat2);
    printf("Enter the y2: ");
    scanf("%f", &lon2);

    double dlat = (lat2 - lat1) * (M_PI / 180.0);
    double dlon = (lon2 - lon1) * (M_PI / 180.0);
    lat1 = lat1 * (M_PI / 180.0);
    lat2 = lat2 * (M_PI / 180.0);

    double a = pow(sin(dlat / 2), 2) + pow(sin(dlon / 2), 2) * cos(lat1) * cos(lat2);
    double c = 2 * asin(sqrt(a));
    double d = radius * c;

    return 0;
}