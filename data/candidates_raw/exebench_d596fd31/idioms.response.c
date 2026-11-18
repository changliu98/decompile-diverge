int itoa(int value, char *str, int base)
{
  char *digits = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  if (base < 2 || base > 36)
    return 0;
  if (value == 0)
  {
    *str = '0';
    return 1;
  }
  char buf[20];
  unsigned long i = 0;
  while (value != 0)
  {
    int digit = value % base;
    value /= base;
    buf[i++] = digits[digit];
  }
  unsigned long j = 0;
  for (j = 0; j < i; j++)
    str[j] = buf[i - j - 1];
  return j;
}