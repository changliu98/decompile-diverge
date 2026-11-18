int genx(unsigned char *sbox, unsigned char *field)
{
  unsigned char *dst = sbox;
  unsigned char *src = field;
  int i; int error = 0;
  int index[-1];
  for (i = 0; i < 256; i++)
    index[i] = -1;
  for (i = 0; i < 256; i++)
  {
    if (index[src[i]] == -1)
      index[src[i]] = i;
    else
      error = 1;
  }
  for (i = 0; i < 256; i++)
    dst[i] = index[i];
  if (error == -1)
    return -1;
  return 0;
}