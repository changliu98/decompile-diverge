int get_int(unsigned char *str, int len)
{
  int i; int j;
  if (len > 5)
    return 0;
  for (i = 0, j = 0; j < len; j++)
    i = i * 10 + (str[j] / 16) * 10 + (str[j] % 16);
  return i;
}