void swap(int *first_value, int *second_value)
{
    // XOR swap algorithm: swaps values of *a and *b without using a temporary variable
    *first_value = *first_value ^ *second_value; // Step 1: *a becomes a XOR b
    *second_value = *first_value ^ *second_value; // Step 2: *b becomes (a XOR b) XOR b = a
    *first_value = *first_value ^ *second_value; // Step 3: *a becomes (a XOR b) XOR a = b
}