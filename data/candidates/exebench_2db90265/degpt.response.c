int inicializa(int *array, int size, int *min_val, int *max_val)
{
    int start_index;
    // If the number of elements is even, initialize min and max using the first two elements
    if (size % 2 == 0) {
        start_index = 2;
        // Compare the first two elements to set initial min and max
        if (*array < array[1]) {
            *min_val = *array;
            *max_val = array[1];
        } else {
            *min_val = array[1];
            *max_val = *array;
        }
    } else {
        // If the number of elements is odd, initialize min and max with the first element
        *min_val = *array;
        *max_val = *array;
        start_index = 1;
    }
    // Return the starting index for the next iteration
    return start_index;
}