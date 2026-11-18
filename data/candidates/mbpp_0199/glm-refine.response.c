int __cdecl func0(int n)
{
  // A number 'n' is a power of 2 if and only if it is greater than 0 
  // and (n & (n - 1)) == 0. This clears the lowest set bit.
  // The expression ((n - 1) & n) == 0 is a standard power-of-two check.
  while (n > 0)
  {
    if ((n & (n - 1)) == 0)
      return n;
    --n;
  }
  
  return 0;
}