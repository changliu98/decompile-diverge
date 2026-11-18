void swap2int(int *first_value, int *second_value)
{
    // Only perform swap if the values are different to avoid unnecessary operations
    if (*first_value != *second_value) {
        // XOR swap algorithm: swaps values without using a temporary variable
        *first_value = *first_value ^ *second_value;  // val1 now holds the XOR of both values
        *second_value = *first_value ^ *second_value;  // val2 becomes the original value of val1
        *first_value = *first_value ^ *second_value;  // val1 becomes the original value of val2
    }
}