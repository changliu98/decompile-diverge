/**
 * Converts a signed integer to its unsigned representation based on a sign bit.
 * If the sign bit is set in *value, the value is treated as negative and converted
 * to its two's complement unsigned equivalent.
 *
 * @param sign_bit The mask representing the sign bit (e.g., 0x80 for 8-bit, 0x8000 for 16-bit).
 * @param value Pointer to the integer value to be converted.
 */
void conv_sign(uint sign_mask, int *num_ptr)
{
  // Check if the sign bit is set in the value
  if ((*num_ptr & sign_mask) != 0) {
    // Calculate the two's complement to convert negative signed value to unsigned
    // This is equivalent to: *value = (int)(unsigned int)*value;
    *num_ptr = sign_mask * 2 - *num_ptr;
    *num_ptr = -*num_ptr;
  }
}