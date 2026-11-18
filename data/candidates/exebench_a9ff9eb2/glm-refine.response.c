void __cdecl ltox(unsigned int value, char *str)
{
  // The lookup table for hexadecimal characters
  const char *hex_table = "0123456789ABCDEF";
  
  // Convert the 32-bit integer to an 8-character hex string (little-endian order)
  for (int i = 0; i < 8; ++i)
  {
    str[9 - i] = hex_table[value & 0xF];
    value >>= 4;
  }
  
  // Prepend the "0x" prefix
  str[0] = '0';
  str[1] = 'x';
  
  // Append a newline and null-terminator
  str[10] = '\n';
  str[11] = '\0';
}