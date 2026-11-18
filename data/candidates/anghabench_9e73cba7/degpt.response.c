/*
 * Check if the given address fits within the range of a 32-bit signed integer.
 * This is used to determine if the address is in the "compatibility space"
 * (i.e., can be safely cast to and from a 32-bit int without loss of information).
 *
 * Returns 1 if the address is within the 32-bit signed integer range, 0 otherwise.
 */
int uasm_in_compat_space_p(long address)
{
  /* Cast the address to int and back to long; if they are equal, the address
     fits within the 32-bit signed integer range. */
  return (int)(address == (int)address);
}