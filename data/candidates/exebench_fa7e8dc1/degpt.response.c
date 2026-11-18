void fancySwap(int *a, int *b)
{
  // XOR first with second and store in first
  *a = *a ^ *b;
  // XOR first (which now holds first^second) with second to get original first value, store in second
  *b = *a ^ *b;
  // XOR first (which holds first^second) with second (which now holds original first) to get original second value, store in first
  *a = *a ^ *b;
}