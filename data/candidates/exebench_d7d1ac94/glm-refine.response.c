int __cdecl imul_dbl(unsigned __int64 *m)
{
  // Extract the two 64-bit operands from the 128-bit integer
  unsigned __int64 low = m[0];
  unsigned __int64 high = m[1];

  // Perform a 128-bit multiplication
  // The lower 64 bits of the result
  unsigned __int64 res_low = low * high;
  // The upper 64 bits of the result
  unsigned __int64 res_high = (__int64)high * (__int128)low >> 64;

  // Store the 128-bit result back into the array
  m[0] = res_low;
  m[1] = res_high;

  // Return 1 if there is an overflow (upper 64 bits are non-zero), 0 otherwise
  return res_high != 0;
}