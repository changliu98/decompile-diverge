int func0(int *array_a, int *array_b, int size)
{
    int total_difference = 0; // Initialize sum to zero
    int index;       // Loop counter
    sort(array_a, size);  // Sort array a in ascending order
    sort(array_b, size);  // Sort array b in ascending order
    for (index = 0; index < size; index++) {
        total_difference += abs(array_a[index] - array_b[index]); // Add the absolute difference between corresponding elements of sorted arrays
    }
    return total_difference; // Return the total sum of absolute differences
}