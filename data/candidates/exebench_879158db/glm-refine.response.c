unsigned __int64 __cdecl xorshf96(unsigned __int64 *x, unsigned __int64 *y, unsigned __int64 *z)
{
  unsigned __int64 t = *x;

  // Apply state transition to 'x'
  *x ^= *x << 16;
  *x ^= *x >> 5;
  *x ^= *x << 1;   // 2 * *x is equivalent to a left shift by 1

  // Rotate the state pointers (x -> y -> z)
  *x = *y;
  *y = *z;
  
  // Calculate the new 'z' and return it
  *z = *y ^ *x ^ t;
  return *z;
}