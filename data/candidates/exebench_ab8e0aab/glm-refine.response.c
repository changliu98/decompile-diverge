/**
 * @brief Finalizes a CRC32 checksum.
 * 
 * In the CRC32 algorithm (e.g., standard zlib/PNG), the accumulator is 
 * initialized to 0xFFFFFFFF. To generate the final checksum, the bitwise 
 * complement (NOT) of the accumulated value is taken.
 * 
 * @param crc Pointer to the CRC32 accumulator/state to be finalized.
 */
void __cdecl crc32_final(unsigned int *crc)
{
  *crc = ~*crc;
}