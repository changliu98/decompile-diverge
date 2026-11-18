int __cdecl div_dbl(unsigned __int64 *u, unsigned __int64 v)
{
  unsigned __int128 dividend;

  // Return 1 on error: null pointer or division overflow 
  // (if the high 64 bits of the dividend are >= divisor, the quotient won't fit in 64 bits)
  if (!u || u[1] >= v)
    return 1;

  // Load the 128-bit dividend from the array
  dividend = *(unsigned __int128 *)u;

  // Store the 128-bit quotient and 64-bit remainder back into the array
  *(unsigned __int128 *)u = dividend / v;
  u[1] = dividend % v;

  return 0;
}