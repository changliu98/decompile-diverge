void __cdecl to_bytes(int val, char *bytes)
{
  // Cast to unsigned to ensure well-defined bitwise shifting and masking
  unsigned int uval = (unsigned int)val;
  
  // Little-endian byte extraction
  bytes[0] = (char)(uval & 0xFF);         // Byte 0 (LSB)
  bytes[1] = (char)((uval >> 8) & 0xFF);  // Byte 1
  bytes[2] = (char)((uval >> 16) & 0xFF); // Byte 2
  bytes[3] = (char)((uval >> 24) & 0xFF); // Byte 3 (MSB)
}