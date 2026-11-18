// Swaps the values pointed to by a and b if *a is less than *b,
// ensuring that *a >= *b after the function call.
void descending2(int *first_value, int *second_value)
{
    // Check if the value at a is less than the value at b
    if (*first_value < *second_value) {
        // Store the value of *a in a temporary variable
        int temporary_holder = *first_value;
        // Assign the value of *b to *a
        *first_value = *second_value;
        // Assign the original value of *a (stored in temp) to *b
        *second_value = temporary_holder;
    }
}