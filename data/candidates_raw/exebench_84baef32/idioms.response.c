void int2hex(unsigned int val, char *buf)
{
  unsigned int i;
  for (i = 0; i < 8; i++) {
    buf[7 - i] = itoa_hex_hexatab[val & 0xf];
    val >>= 4;
  }
}