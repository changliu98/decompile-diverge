// Swap the values pointed to by x and y using XOR operations
void inplace_swap(int *ptr_a, int *ptr_b)
{
    // Step 1: y becomes x ^ y
    *ptr_b = *ptr_a ^ *ptr_b;
    // Step 2: x becomes x ^ (x ^ y) = y
    *ptr_a = *ptr_a ^ *ptr_b;
    // Step 3: y becomes (x ^ y) ^ y = x
    *ptr_b = *ptr_a ^ *ptr_b;
}