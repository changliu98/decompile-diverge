void __cdecl shiftarray(int *a)
{
  // Loop unrolling or standard array shift representation
  for (int i = 0; i < 9; ++i)
  {
    a[i] = a[i + 1];
  }
  
  // Set the vacated last slot to -1 (often used as a sentinel or null value)
  a[9] = -1;
}