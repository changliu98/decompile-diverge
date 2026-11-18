int func0(int *arr, int size)
{
    // Base case: if only one element, return it
    if (size == 1) {
        return *arr;
    }
    // Initialize local_c and min_so_far with the first element
    int current_min_sum = *arr;
    int global_min = *arr;
    // Iterate through the rest of the array
    for (int index = 1; index < size; index++) {
        int element = arr[index];
        // Calculate potential new minimum sum ending at current position
        int potential_min = current_min_sum + element;
        // If the new sum is greater than the overall minimum so far, keep the overall minimum
        if (potential_min > global_min) {
            potential_min = global_min;
        }
        // Update local_c to be the new minimum sum ending at current position
        current_min_sum = potential_min;
        // Update the overall minimum element seen so far
        if (element < global_min) {
            global_min = element;
        }
    }
    // Return the minimum sum found
    return current_min_sum;
}