void __cdecl pick(int *x, int *y)
{
  // Increment the column/row tracker and check for horizontal overflow
  if ( ++*y >= 768 )
  {
    ++*x;     // Advance to the next row
    *y = 0;   // Reset column tracker
  }

  // Check for vertical overflow and wrap around
  if ( *x >= 180 )
  {
    *x = 0;   // Reset row tracker
  }
}