void yxyDES2_Int2Bits(int i, char *bits)
{
  int j = 0;
  for (j = 0; j < 4; j++)
  {
    bits[j] = (char)(((i << j) & 0x08) >> 3);
  }
}