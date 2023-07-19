#if !defined(EUCLID_H)
#define EUCLID_H

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


#endif // EUCLID_H
