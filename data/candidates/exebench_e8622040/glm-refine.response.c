int __cdecl doit(int *x, int y)
{
  // Check if the current value is strictly greater than the new value
  if (*x > y)
  {
    // Update the value
    *x = y;
    return 1; // Update succeeded
  }
  
  return 0; // No update performed
}