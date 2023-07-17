#include <stdio.h>
#include <assert.h>

// Recursive implementation of binary search
int binarySearchRecursive(const int *arr, int leftIndex, int rightIndex, int target);

// Iterative implementation of binary search
int binarySearchIterative(const int *arr, int leftIndex, int rightIndex, int target);

// Test implementations
void test();

int main()
{
    test();
    return 0;
}

// Recursive implementation of binary search
int binarySearchRecursive(const int *arr, int leftIndex, int rightIndex, int target)
{
    if (rightIndex >= leftIndex)
    {
        int mid = leftIndex + (rightIndex - leftIndex) / 2;

        if (arr[mid] == target)
            return mid;

        if (arr[mid] > target)
            return binarySearchRecursive(arr, leftIndex, mid - 1, target);

        return binarySearchRecursive(arr, mid + 1, rightIndex, target);
    }

    return -1;
}

// Iterative implementation of binary search
int binarySearchIterative(const int *arr, int leftIndex, int rightIndex, int target)
{
    while (leftIndex <= rightIndex)
    {
        int mid = leftIndex + (rightIndex - leftIndex) / 2;

        if (arr[mid] == target)
            return mid;

        if (arr[mid] > target)
            rightIndex = mid - 1;
        else
            leftIndex = mid + 1;
    }

    return -1;
}

void test()
{
    int arr[] = {2, 3, 4, 10, 40};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Test 1... ");
    int target = 10;
    int result = binarySearchRecursive(arr, 0, n - 1, target);
    assert(result == 3);
    printf("passed recursive, ");
    result = binarySearchIterative(arr, 0, n - 1, target);
    assert(result == 3);
    printf("passed iterative.\n");

    printf("Test 2... ");
    target = 5;
    result = binarySearchRecursive(arr, 0, n - 1, target);
    assert(result == -1);
    printf("passed recursive, ");
    result = binarySearchIterative(arr, 0, n - 1, target);
    assert(result == -1);
    printf("passed iterative.\n");
}
