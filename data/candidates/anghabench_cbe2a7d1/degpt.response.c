/*
 * Calculate the register offset for VPC Stream Out Buffer configuration.
 *
 * @param i0: Stream out buffer index (0-based).
 * @return: The calculated register offset address for the specified buffer.
 */
uint32_t REG_A5XX_VPC_SO_BUFFER_OFFSET(uint32_t stream_out_buffer_index)
{
  return stream_out_buffer_index * 7 + 0xe2ab;
}