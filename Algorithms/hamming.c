#include <stdio.h>
#include <stdbool.h>

// Function to calculate the Hamming code for a given data
void hammingCode(int data[], int size, int parityBits) {
    // Calculate the number of bits required for the code
    int totalBits = size + parityBits;
    
    // Create an array to store the Hamming code
    int hammingCode[totalBits];
    
    // Initialize all bits to 0
    for (int i = 0; i < totalBits; i++) {
        hammingCode[i] = 0;
    }

    // Copy the data bits into the Hamming code array
    int dataIndex = 0;
    for (int i = 0; i < totalBits; i++) {
        if ((i & (i - 1)) != 0) {  // Skip powers of 2 (parity bit positions)
            hammingCode[i] = data[dataIndex];
            dataIndex++;
        }
    }

    // Calculate the parity bits
    for (int i = 0; i < parityBits; i++) {
        int parityBitIndex = 1 << i;
        int parity = 0;

        for (int j = parityBitIndex; j < totalBits; j++) {
            if ((j & parityBitIndex) != 0) {
                parity ^= hammingCode[j];
            }
        }

        hammingCode[parityBitIndex] = parity;
    }

    // Output the Hamming code
    printf("Hamming Code: ");
    for (int i = 1; i < totalBits; i++) {
        printf("%d", hammingCode[i]);
    }
    printf("\n");
}

int main() {
    // Sample input data
    int data[] = {1, 0, 1, 0};
    int size = sizeof(data) / sizeof(data[0]);
    int parityBits = 0;

    // Calculate the number of parity bits required
    while ((1 << parityBits) < size + parityBits + 1) {
        parityBits++;
    }

    // Output the input data
    printf("Input Data: ");
    for (int i = 0; i < size; i++) {
        printf("%d", data[i]);
    }
    printf("\n");

    // Generate and output the Hamming code
    hammingCode(data, size, parityBits);

    return 0;
}
