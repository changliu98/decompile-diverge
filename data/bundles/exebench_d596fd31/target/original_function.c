static size_t
itoa (unsigned int value, char* str, unsigned int base)
{
  char* digits = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  char tmp[32];

  if (base < 2 || base > 36) return 0;

  if (value == 0)
    {
      str[0] = '0';
      return 1;
    }

  size_t current = 0;
  while (value)
    {
      int index = value % base;
      value = value / base;

      tmp[current] = digits[index];
      current++;
    }

  size_t i = 0;
  for (; i < current; i++)
    {
      str[i] = tmp[current - 1 - i];
    }

  return i;
}