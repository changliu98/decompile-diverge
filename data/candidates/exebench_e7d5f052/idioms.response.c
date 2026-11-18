void SJIStoJIS(unsigned char *a, unsigned char *b)
{
  unsigned char c1 = *a;
  unsigned char c2 = *b;
  int a1 = c1 - (c1 < 0xa0 ? 128 : 176);
  int a2 = c2 - (c2 < 0x9f ? (c2 < 0x80 ? 32 : 64) : 126);
  *a = a1 * 2 + a2 - 159;
  *b = c2 - a2;
}