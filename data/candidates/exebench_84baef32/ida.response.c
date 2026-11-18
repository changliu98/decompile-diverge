void __cdecl itoa_hex(unsigned int val, char *buf)
{
  unsigned int i; // [rsp+0h] [rbp-14h]

  for ( i = 0; i < 8; ++i )
  {
    buf[7 - i] = itoa_hex_hexatab[val & 0xF];
    val >>= 4;
  }
}