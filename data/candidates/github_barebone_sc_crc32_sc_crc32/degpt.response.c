/**
 * Calculate the CRC32 checksum for a given buffer.
 *
 * @param crc Initial CRC value (typically 0xFFFFFFFF for a new calculation).
 * @param buf Pointer to the data buffer to compute the CRC over.
 * @param len Length of the data buffer in bytes.
 * @return The computed CRC32 checksum.
 */
uint32_t sc_crc32(uint32_t initial_crc, void *data_buffer, size_t buffer_length)
{
    // Delegate the CRC32 calculation to the software-based little-endian implementation.
    return crc32_sw_le(initial_crc, data_buffer, buffer_length);
}