/**
 * @brief Computes a running 8-bit XOR checksum (often mislabeled as CRC).
 * 
 * @param current_crc Pointer to the current checksum value. 
 *                    Modified in-place to include `new_byte`.
 * @param new_byte    The next byte of data to incorporate into the checksum.
 */
void __cdecl update_xor_checksum(unsigned char *current_crc, unsigned char new_byte)
{
    *current_crc ^= new_byte;
}