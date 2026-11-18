int __cdecl str_to_int(const char *str, int *num)
{
  int base = 10;
  int i = 0;

  *num = 0;

  // Check for "0x" or "0X" prefix to switch to hexadecimal parsing
  // __PAIR64__(str[1], *str) == 0x7800000030 checks if str[0]=='0' (0x30) and str[1]=='x' (0x78)
  if (str[0] == '0' && (str[1] == 'x' || str[1] == 'X'))
  {
    i = 2;
    base = 16;
  }

  // Empty string or string with only "0x" prefix
  if (!str[i])
    return -1;

  while (str[i])
  {
    int digit;

    if (str[i] >= '0' && str[i] <= '9')
    {
      digit = str[i] - '0';
    }
    else if (base == 16)
    {
      if (str[i] >= 'A' && str[i] <= 'F')
      {
        digit = str[i] - 'A' + 10;
      }
      else if (str[i] >= 'a' && str[i] <= 'f')
      {
        digit = str[i] - 'a' + 10;
      }
      else
      {
        return -1; // Invalid hexadecimal character
      }
    }
    else
    {
      return -1; // Invalid decimal character
    }

    *num = *num * base + digit;
    ++i;
  }

  return 0;
}