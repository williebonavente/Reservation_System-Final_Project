#include <stdio.h>
#include <stdbool.h>

// Function to calculate the Sørensen–Dice coefficient between two sets
double diceCoefficient(const int set1[], const int set2[], int size1, int size2) {
    int intersection = 0;

    // Calculate the intersection of the sets
    for (int i = 0; i < size1; i++) {
        for (int j = 0; j < size2; j++) {
            if (set1[i] == set2[j]) {
                intersection++;
                break;
            }
        }
    }
    
    // Calculate the Sørensen–Dice coefficient
    if (size1 + size2 == 0) {
        return 0.0;
    }

    return (2.0 * intersection) / (size1 + size2);
}

int main() {
    // Sample input sets (represented as arrays)
    int set1[] = {1, 2, 3, 4, 5};
    int set2[] = {3, 4, 5, 6, 7};
    int size1 = sizeof(set1) / sizeof(set1[0]);
    int size2 = sizeof(set2) / sizeof(set2[0]);

    // Calculate the Sørensen–Dice coefficient
    double coefficient = diceCoefficient(set1, set2, size1, size2);

    // Output the result
    printf("Sørensen-Dice Coefficient: %.2f\n", coefficient);

    return 0;
}
