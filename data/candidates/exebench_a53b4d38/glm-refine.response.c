void __cdecl foo(int *x, int *y)
{
  int i;

  // Check if the first 8 elements of y match the sequence [2, 3, 4, 5, 6, 7, 8, 9]
  for ( i = 0; i < 8; ++i )
  {
    if (y[i] != i + 2)
      break;
  }

  // If the sequence matches and *x is 1, update *x to 8 and overwrite y with [9, 10, ..., 16]
  if ( i == 8 && *x == 1 )
  {
    *x = 8;
    for ( i = 0; i < 8; ++i )
      y[i] = i + 9;
  }
  else
  {
    // Otherwise, fallback to setting *x to 6
    *x = 6;
  }
}