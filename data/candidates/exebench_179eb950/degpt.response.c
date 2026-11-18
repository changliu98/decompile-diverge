// Swap the values of two integers using XOR operations
void swap_int(int *first, int *second)
{
  // Step 1: x = x ^ y
  *second = *first ^ *second;
  // Step 2: y = (x ^ y) ^ x = y
  *first = *second ^ *first;
  // Step 3: x = (x ^ y) ^ y = x
  *second = *first ^ *second;
}