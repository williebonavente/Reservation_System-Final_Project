#include <stdio.h>
#include <math.h>

// Function to calculate the Minkowski distance between two points
double minkowskiDistance(const double *point1, const double *point2, int dimensions, double p)
{
    double distance = 0.0;

    // Calculate the sum of the absolute differences raised to the power p
    for (int i = 0; i < dimensions; i++)
    {
        distance += pow(fabs(point1[i] - point2[i]), p);
    }

    // Take the p-th root of the sum to get the final distance
    distance = pow(distance, 1.0 / p);

    return distance;
}

int main()
{
    int dimensions;
    printf("Enter the number of dimensions: ");
    scanf("%d", &dimensions);

    double point1[dimensions], point2[dimensions];
    printf("Enter the values of point 1: ");
    for (int i = 0; i < dimensions; i++)
    {
        scanf("%lf", &point1[i]);
    }

    printf("Enter the values of point 2: ");
    for (int i = 0; i < dimensions; i++)
    {
        scanf("%lf", &point2[i]);
    }

    double p;
    printf("Enter the value of p: ");
    scanf("%lf", &p);

    // Calculate the Minkowski distance between the two points
    double distance = minkowskiDistance(point1, point2, dimensions, p);

    printf("The Minkowski distance between the two points is: %lf\n", distance);

    return 0;
}
