void __cdecl decode_dir(short d, int *x, int *y)
{
  // Extract the lower 8 bits for X and the upper 8 bits for Y.
  // Both are offset by subtracting 2 (likely to center a 5x5 grid around 0,0).
  *x = (unsigned __int8)d - 2;
  *y = ((d & 0xFF00) >> 8) - 2;
}