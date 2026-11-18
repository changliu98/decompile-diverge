// Calculates a checksum for the given buffer.
// Parameters:
//   buff     - Pointer to the buffer containing data.
//   len      - Length of the buffer in bytes.
//   result   - Initial checksum value to add to the calculation.
// Returns:
//   The computed checksum value.
unsigned_long do_csum(uchar *buffer, int buffer_length, unsigned_long initial_checksum)
{
  // Check if the buffer pointer is not aligned to a 4-byte boundary.
  // If the address is odd (not divisible by 4), return an adjusted result.
  if (((ulong)buffer & 2) != 0) {
    return initial_checksum + 1;
  }
  // If the buffer is properly aligned, return the original result.
  return initial_checksum;
}