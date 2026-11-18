void __cdecl inplace_swap(int *x, int *y)
{
  *y ^= *x; // Step 1: *y = *y ^ *x
  *x ^= *y; // Step 2: *x = *x ^ (*y ^ *x) = *x ^ *y ^ *x = *y (original)
  *y ^= *x; // Step 3: *y = (*y ^ *x) ^ *y = *x (original)
}