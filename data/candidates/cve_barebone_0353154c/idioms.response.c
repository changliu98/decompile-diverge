void bit_write_UMC(struct bitchain *chain, unsigned long long val)
{
  struct bitchain *c = chain;
  unsigned long long v = val;
  unsigned long long mask = 0x7f;
  int i = 4;
  int j = 0;
  unsigned char byte[5];
  for ( ; i >= 0; i--) {
    byte[i] = (unsigned char)(((mask & v) >> j) & 0xff);
    byte[i] |= 0x80;
    mask = mask << 7;
    i--;
    j += 7;
  }
  for (i = 0; i < 4 && (byte[i] & 0x7f) == 0; i++)
    ;
  if (byte[i] & 0x40)
    i--;
  byte[i] &= ~0x80;
  for (j = 4; j >= i; j--)
    bitcode_ubyte(c, (unsigned char)(byte[j]));
}