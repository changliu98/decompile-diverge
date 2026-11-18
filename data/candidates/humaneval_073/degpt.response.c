int func0(int *array, int array_length)
{
    int mismatch_count = 0; // Initialize counter for mismatched pairs
    for (int index = 0; index < array_length / 2; index++) { // Iterate through the first half of the array
        if (array[index] != array[array_length - 1 - index]) { // Compare element at index i with its symmetric counterpart from the end
            mismatch_count++; // Increment counter if elements do not match
        }
    }
    return mismatch_count; // Return the total count of mismatched pairs
}