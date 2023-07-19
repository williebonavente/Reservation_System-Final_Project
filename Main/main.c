#include <stdio.h>
#include "../libs/euclid.h"

int main(void)
{
    int a, b;
    printf("Enter two numbers: "); 
    scanf("%i%i", &a,&b);
    int GCD = euclideanGCD(a, b);
    printf("%i ", GCD);

    return 0;
}
