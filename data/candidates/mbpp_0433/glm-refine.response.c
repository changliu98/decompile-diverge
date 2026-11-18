#include <stdio.h>

// Renamed function and variables for better readability based on their behavior
void check_if_number_is_greater(int *arr, int size, int number) 
{
    // Step 1: Sort the array in ascending order using Bubble Sort
    for (int i = 0; i < size - 1; ++i) 
    {
        for (int j = 0; j < size - i - 1; ++j) 
        {
            if (arr[j] > arr[j + 1]) 
            {
                // Swap elements
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

    // Step 2: Compare the input number with the maximum element in the array
    // Since the array is sorted, the maximum element is at the last index
    if (number <= arr[size - 1])
        printf("No, entered number is less than those in the array\n");
    else
        printf("Yes, the entered number is greater than those in the array\n");
}