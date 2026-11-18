int __cdecl func0(int n)
{
  char bit_count; // Tracks the number of bits shifted
  int na;         // Working copy of n

  na = n;
  bit_count = 0;

  // Check if n is non-zero and a power of 2.
  // A number is a power of 2 if it has exactly one bit set.
  // (n & (n - 1)) == 0 checks this condition.
  if ( n && ((n - 1) & n) == 0 )
    return n;

  // If not a power of 2, count the number of bits required to represent 'n'.
  // This effectively calculates floor(log2(n)) + 1.
  while ( na )
  {
    na >>= 1;
    ++bit_count;
  }

  // Return 2^bit_count, which is the next power of 2.
  return 1 << bit_count;
}