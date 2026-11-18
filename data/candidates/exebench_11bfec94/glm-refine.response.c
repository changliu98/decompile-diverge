void __cdecl to_hex(long x, char *c)
{
  const char *hex_chars = "0123456789ABCDEF";
  
  // Write 4 hex characters (16 bits) in big-endian order
  for (int i = 3; i >= 0; --i)
  {
    c[i] = hex_chars[x & 15]; // Equivalent to x % 16
    x >>= 4;                  // Equivalent to x /= 16
  }
  
  c[4] = '\0'; // Null-terminate the string
}