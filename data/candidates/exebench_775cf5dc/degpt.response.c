void AddArray2(float *source_array, float *target_array, int array_length)
{
    // Iterate through the arrays in steps of 2 for vectorization
    for (int index = 0; index < array_length; index += 2) {
        // Add corresponding element from array a to array b
        target_array[index] += source_array[index];
        // Add next corresponding element from array a to array b
        target_array[index + 1] += source_array[index + 1];
    }
}