int func0(int *arr, int size)
{
    // Initialize mx to the minimum possible integer value
    int max_val = -0x80000000;
    // Start loop from the second element (index 1)
    int index = 1;
    // Iterate through the array from index 1 to n-1
    while (index < size) {
        // If current element is less than mx, return 0 (condition fails)
        if (arr[index] < max_val) {
            return 0;
        }
        // Update mx to be the maximum of mx and the previous element
        if (max_val < arr[index - 1]) {
            max_val = arr[index - 1];
        }
        // Move to the next element
        index++;
    }
    // If all elements satisfy the condition, return 1
    return 1;
}