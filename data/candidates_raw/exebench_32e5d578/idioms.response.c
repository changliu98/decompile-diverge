void int2bin(unsigned int n, int *binary)
{
  int i;
  for (i = 0; i < 8; i++) {
    if (n & 0x80)
      binary[i] = 1;
    else
      binary[i] = 0;
    n = n << 1;
  }
}