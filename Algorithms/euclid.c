#include <stdio.h>

// Function to find the greatest common divisor (GCD) using the Euclidean algorithm
int euclideanGCD(int a, int b)
{
    // Ensure a is greater than or equal to b
    if (a < b)
    {
        int temp = a;
        a = b;
        b = temp;
    }

    while (b != 0)
    {
        int remainder = a % b;
        a = b;
        b = remainder;
    }

    return a;
}

int main()
{
    int num1, num2;
    
    printf("Enter two numbers to find their GCD: ");
    scanf("%d %d", &num1, &num2);

    // Calculate the GCD using the Euclidean algorithm
    int gcd = euclideanGCD(num1, num2);

    printf("The GCD of %d and %d is: %d\n", num1, num2, gcd);
    return 0;
}
