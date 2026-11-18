// Adds the values pointed to by a and b, storing the result in the location pointed to by result
void my_add(int *value_a, int *value_b, int *output)
{
    // Compute the sum of the dereferenced pointers a and b
    *output = *value_a + *value_b;
}