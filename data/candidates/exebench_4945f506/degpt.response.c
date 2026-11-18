void add3(double *source_array, double *target_array)
{
    // Add the first element of array a to the first element of array b
    *target_array = *source_array + *target_array;
    // Add the second element of array a to the second element of array b
    target_array[1] = source_array[1] + target_array[1];
    // Add the third element of array a to the third element of array b
    target_array[2] = source_array[2] + target_array[2];
}