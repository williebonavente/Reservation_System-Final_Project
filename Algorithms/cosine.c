#include <stdio.h>
#include <math.h>

// Function to calculate the dot product of two vectors
double dotProduct(const double vector1[], const double vector2[], int size) {
    double dotProduct = 0.0;
    for (int i = 0; i < size; i++) {
        dotProduct += vector1[i] * vector2[i];
    }
    return dotProduct;
}

// Function to calculate the magnitude (Euclidean norm) of a vector
double magnitude(const double vector[], int size) {
    double sumOfSquares = 0.0;
    for (int i = 0; i < size; i++) {
        sumOfSquares += vector[i] * vector[i];
    }
    return sqrt(sumOfSquares);
}

// Function to calculate the cosine similarity between two vectors
double cosineSimilarity(const double vector1[], const double vector2[], int size) {
    double dotProd = dotProduct(vector1, vector2, size);
    double magVector1 = magnitude(vector1, size);
    double magVector2 = magnitude(vector2, size);

    if (magVector1 == 0 || magVector2 == 0) {
        return 0.0;
    }

    return dotProd / (magVector1 * magVector2);
}

int main() {
    // Sample input vectors
    double vector1[] = {2.0, 3.0, 1.0};
    double vector2[] = {1.0, 2.0, 3.0};
    int size = sizeof(vector1) / sizeof(vector1[0]);

    // Calculate the cosine similarity
    double similarity = cosineSimilarity(vector1, vector2, size);

    // Output the result
    printf("Cosine Similarity: %.2f\n", similarity);

    return 0;
}
