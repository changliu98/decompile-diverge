int strtol(char *str, unsigned long *val)
{
  unsigned long i = 0;
  unsigned long result = 0;
  for (;;)
  {
    unsigned long digit = (str[i] - '0');
    if (digit >= 8)
      break;
    result = (result * 8) + digit;
    i++;
  }
  *val = result;
  return i;
}