#include <limits.h>

// func1 sorts the input array in ascending order using the bubble sort algorithm,
// then finds and returns the minimum difference between any two consecutive elements.
// If the array has fewer than 2 elements, the loops are bypassed and it returns INT_MAX.
int __cdecl func1(int *arr, int n)
{
    // 1. Bubble Sort: Sort the array in ascending order
    for (int i = 0; i < n - 1; ++i)
    {
        for (int j = 0; j < n - i - 1; ++j)
        {
            if (arr[j] > arr[j + 1])
            {
                // Swap arr[j] and arr[j + 1]
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

    // 2. Find Minimum Difference: Find the minimum difference between consecutive elements
    int min_diff = INT_MAX; // 0x7FFFFFFF is the maximum value for a 32-bit signed integer
    for (int i = 0; i < n - 1; ++i)
    {
        int current_diff = arr[i + 1] - arr[i];
        if (current_diff < min_diff)
        {
            min_diff = current_diff;
        }
    }

    return min_diff;
}