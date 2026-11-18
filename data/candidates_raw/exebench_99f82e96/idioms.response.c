char *itoa(int value, char *str, int base)
{
  int i = value;
  char *s = str;
  char *low;
  if (base < 2 || base > 36)
    {
      *str = '\0';
      return str;
    }
  if (i < 0)
    {
      *s++ = '-';
      i = -i;
    }
  low = s;
  do
    {
      *s++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz"[35 + i % base];
    }
  while (i /= base);
  *s-- = '\0';
  while (low < s)
    {
      char tmp = *low;
      *low++ = *s;
      *s-- = tmp;
    }
  return str;
}