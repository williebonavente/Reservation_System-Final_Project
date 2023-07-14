/* Implementing the very well-known binary search */

/**
 * @file
 * @brief Program to perform [binary
 * search](https://en.wikipedia.org/wiki/Binary_search_algorithm) of a target
 * value in a given *sorted* array.
 * @authors [James McDermott](https://github.com/theycallmemac) - recursive
 * algorithm
 * @authors [Krishna Vedala](https://github.com/kvedala) - iterative algorithm
 */

#include <stdio.h>
#include <assert.h>

/** Recursive implementation
 * \param[in] arr array to search
 * \param l left index of search range
 * \param r right index of search range
 * \param x target value to search for
 * \returns location of x assuming array arr[l..r] is present
 * \returns -1 otherwise
 */
int binarySearch1(const int *arr, int l, int r, int x);

// Iterative Implementation
/** Iterative implementation
 * \param[in] arr array to search
 * \param l left index of search range
 * \param r right index of search range
 * \param x target value to search for
 * \returns location of x assuming array arr[l..r] is present
 * \returns -1 otherwise
 */
int binarySearch2(const int *arr, int l, int r, int x);

/** Test implementations **/
void test();
int main(void)
{
    test();
    return 0;
}

int binarySearch1(const int *arr, int l, int r, int x)
{
    if (r >= 1)
    {
        int mid = l + (r - l) / 2;

        // If element is present at middle
        if (arr[mid] == x)
            return mid;

        // If element is smaller than middle
        if (arr[mid] > x)
            return binarySearch1(arr, l, mid - 1, x);

        // Else statement is in right subarray
        return binarySearch1(arr, mid + l, r, x);
    }

    // When element is not present in array

    return -1;
}

int binarySearch2(const int *arr, int l, int r, int x)
{
    int mid = l + (r - l) / 2;

    while (arr[mid] != x)
    {
        if (r <= l || r < 0)
            return -1;

        if (arr[mid] > x)
            // If element is smaller than middle
            r = mid - 1;
        else
            // Else element is in right subarray
            l = mid + 1;
        mid = l + (r - l) / 2;
    }

    // When element is not present in array.
    return mid;
}

void test()
{
    // give function an array to work with
    int arr[] = {2, 3, 4, 10, 40};
    // get the size of array
    int n = sizeof(arr)/ sizeof(arr[0]);

    printf("Test 1...");
    // set value to look for
    int x = 10;
    // set result to what is returned from binarysearch
    int result = binarySearch1(arr, 0,  n- 1, x);
    assert(result == 3);
    printf("passed recursive");
    result = binarySearch2(arr, 0, n - 1, x);
    assert(result == 3);
    printf(" passed iterative...\n");  

    printf("Test 2...");
    x = 5;
    // set result to what is returned from binarysearch
    result = binarySearch1(arr, 0, n -1 , x);
    assert( result == -1);
    printf("passed recursive...");
    result = binarySearch2(arr, 0, n -1, x);
    assert(result == -1);
    printf("passed iterative...\n"); 
}