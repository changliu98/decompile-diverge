void endian_swap32bit(uint *value)
{
  // Swap bytes of a 32-bit unsigned integer in-place
  // Move byte 0 to position 3, byte 1 to position 2,
  // byte 2 to position 1, and byte 3 to position 0
  *value = *value >> 0x18 | (*value & 0xff00) << 8 | *value >> 8 & 0xff00 | *value << 0x18;
}