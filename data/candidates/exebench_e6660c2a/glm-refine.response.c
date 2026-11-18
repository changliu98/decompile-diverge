void __cdecl foo(int *x, int y, int z)
{
  int c = x[0];
  int d = x[1];
  
  // The loop `for (b = 0; b < 1; ++b)` executes exactly once with b = 0.
  // Thus, `b + 2` is always 2, and `1 >> b` is always `1 >> 0 = 1`.
  
  // Evaluate boolean conditions to 1 (true) or 0 (false)
  int v3 = d ? 2 : 0;
  int v4 = c ? 2 : 0;
  
  // Bitwise OR the evaluated flags together
  x[2] = (z != 0) | v3 | (y != 0) | 1 | v4;
}