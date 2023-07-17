#include <stdio.h>
#include <stdlib.h>

// Calculate the Manhattan distance between two points (x1, y1) and (x2, y2)
int manhattanDistance(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}

int main() {
    int x1, y1, x2, y2;

    // Get the coordinates of the first point
    printf("Enter the x-coordinate of the first point: ");
    scanf("%d", &x1);
    printf("Enter the y-coordinate of the first point: ");
    scanf("%d", &y1);

    // Get the coordinates of the second point
    printf("Enter the x-coordinate of the second point: ");
    scanf("%d", &x2);
    printf("Enter the y-coordinate of the second point: ");
    scanf("%d", &y2);

    // Calculate and print the Manhattan distance
    int distance = manhattanDistance(x1, y1, x2, y2);
    printf("The Manhattan distance between (%d, %d) and (%d, %d) is %d\n", x1, y1, x2, y2, distance);

    return 0;
}
