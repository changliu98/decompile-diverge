int __cdecl func0(int n)
{
  // A number 'n' is a power of 2 if and only if it is greater than 0 and 
  // the bitwise AND of 'n' and 'n - 1' equals 0.
  // This works because powers of 2 have exactly one bit set to 1 in binary representation, 
  // and subtracting 1 flips all lower bits, resulting in a 0 when ANDed.
  while (n > 0)
  {
    if (((n - 1) & n) == 0) 
    {
      return n;
    }
    --n;
  }
  
  return 0;
}