/*
 * Unpacks a 32-bit unsigned integer from a 4-byte string in little-endian format.
 *
 * Parameters:
 *   s - Pointer to the first byte of the 4-byte sequence.
 *   u - Pointer to the uint where the unpacked value will be stored.
 *
 * The function reconstructs the 32-bit integer by combining the four bytes:
 *   byte 0 (least significant) +
 *   byte 1 * 0x100 +
 *   byte 2 * 0x10000 +
 *   byte 3 (most significant) * 0x1000000
 */
void ut32_unpack(char *data, uint *result)
{
  /*
   * Reconstruct the 32-bit integer from four bytes in little-endian order.
   * Each byte is cast to unsigned char (via byte) to ensure proper unsigned arithmetic,
   * then shifted and combined to form the final 32-bit value.
   */
  *result = (uint)(byte_cast)*data +
       ((uint)(byte)data[1] + ((uint)(byte)data[2] + (uint)(byte)data[3] * 0x100) * 0x100) * 0x100;
}