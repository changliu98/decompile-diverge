int conv_hstring(char *str, unsigned int *num)
{
  int i = 0;
  unsigned int c;
  int ok = 1;
  *num = 0;
  while (1) {
    c = str[i];
    if ((c >= '0') && (c <= '9'))
      ok = (i < 9);
    else if ((c >= 'a') && (c <= 'f'))
      ok = (i < 9);
    if (!ok)
      break;
    if ((c >= '0') && (c <= '9'))
      *num = *num * 16 + (str[i++] - '0');
    else
      *num = *num * 16 + (str[i++] - 'a') + 10;
  }
  return i;
}