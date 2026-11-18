size_t __cdecl itoa(unsigned int value, char *str, unsigned int base)
{
  char tmp[32];
  const char *digits = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  size_t current = 0;
  size_t i;

  // Validate base (must be between 2 and 36)
  if (base < 2 || base > 36)
    return 0;

  // Handle the zero value as a special case
  if (value == 0)
  {
    str[0] = '0';
    return 1;
  }

  // Convert value to the given base in reverse order
  while (value)
  {
    int index = value % base;
    value /= base;
    tmp[current++] = digits[index];
  }

  // Reverse the string and write it to the output buffer
  for (i = 0; i < current; ++i)
    str[i] = tmp[current - 1 - i];

  return i;
}