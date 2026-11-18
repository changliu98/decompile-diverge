/**
 * @brief   Convert a 32-bit little-endian value to CPU byte order.
 *
 * @param   p   Pointer to the 32-bit value in little-endian format.
 * @return  The converted 32-bit value in CPU byte order.
 */
uint32_t le32_to_cpu(uint32_t *ptr)
{
  return *ptr;
}