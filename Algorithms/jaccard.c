#include <stdio.h>
#include <stdbool.h>

// Function to calculate the Jaccard similarity between two sets
double jaccardSimilarity(const int set1[], const int set2[], int size1, int size2) {
    int intersection = 0;
    int unionSize = 0;

    // Calculate the intersection and union of the sets
    for (int i = 0; i < size1; i++) {
        for (int j = 0; j < size2; j++) {
            if (set1[i] == set2[j]) {
                intersection++;
                break;
            }
        }
    }
    
    unionSize = size1 + size2 - intersection;
    
    // Calculate Jaccard similarity
    if (unionSize == 0) {
        return 0.0;
    }

    return (double)intersection / unionSize;
}

int main() {
    // Sample input sets (represented as arrays)
    int set1[] = {1, 2, 3, 4, 5};
    int set2[] = {3, 4, 5, 6, 7};
    int size1 = sizeof(set1) / sizeof(set1[0]);
    int size2 = sizeof(set2) / sizeof(set2[0]);

    // Calculate the Jaccard similarity
    double similarity = jaccardSimilarity(set1, set2, size1, size2);

    // Output the result
    printf("Jaccard Similarity: %.2f\n", similarity);

    return 0;
}
