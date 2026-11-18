void func0(int *source_array, int source_length, int step_size, int *result_array, int *result_length)
{
    int result_index = 0; // Initialize index for output list
    for (int source_index = 0; source_index < source_length; source_index += step_size) { // Iterate through input list with step size n
        result_array[result_index] = source_array[source_index]; // Copy element from input list to output list
        result_index++; // Increment output list index
    }
    *result_length = result_index; // Set the size of the output list to the number of elements copied
}