int __cdecl safe_calloc_check_mul(size_t a, size_t b, size_t *res)
{
  size_t tmp; // Temporary buffer for the result if 'res' is NULL
  size_t *out_ptr;

  // Determine where to store the multiplication result.
  // If 'res' is provided, use it; otherwise, use the local temporary variable.
  out_ptr = res ? res : &tmp;

  // Perform the multiplication and store the lower 64 bits
  *out_ptr = a * b;

  // Check for overflow:
  // Cast 'a' to a 128-bit unsigned integer, multiply by 'b', and right-shift by 64 bits.
  // If the upper 64 bits of the 128-bit result are 0, there is no overflow (returns 1).
  // Otherwise, an overflow occurred (returns 0).
  return ((unsigned __int128)b * a) >> 64 == 0;
}