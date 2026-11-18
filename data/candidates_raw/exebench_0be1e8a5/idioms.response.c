void itos(char *res, unsigned short i)
{
  unsigned char a;
  unsigned short b;
  b = i / 10000 * 10000;
  res[0] = b / 10000 + '0';
  a = (i - b) / 1000;
  b += a * 1000;
  res[1] = a + '0';
  a = (i - b) / 100;
  b += a * 100;
  res[2] = a + '0';
  a = (i - b) / 10;
  res[3] = a + '0';
  res[4] = i - b - a * 10 + '0';
  res[5] = '\0';
}