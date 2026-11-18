char *__cdecl int2str(int val, char *str, int base)
{
  char buf[33]; // Temporary buffer to hold the digits in reverse order (max 32 bits + null terminator)
  char *p = buf;
  char *p2 = str;
  unsigned int uval;

  memset(buf, 0, sizeof(buf));

  if (base >= 2 && base <= 36)
  {
    uval = val;
    
    // Handle negative numbers exclusively for base 10
    if (val < 0 && base == 10)
      uval = -val;

    // Convert the value to digits in reverse order
    do
    {
      *p++ = int2str_tab[uval % base];
      uval /= (unsigned int)base;
    }
    while (uval);

    // Append the minus sign for negative base-10 numbers
    if (val < 0 && base == 10)
      *p++ = '-';

    // Reverse the generated string from `buf` into the output `str`
    // The loop halts when it encounters a null byte (due to the initial memset)
    for (char *pa = p - 1; ; --pa)
    {
      bool valid = false;
      if (pa >= buf)
      {
        char c = *pa;
        *p2++ = *pa;
        valid = (c != 0);
      }
      if (!valid)
        break;
    }

    *p2 = 0; // Null-terminate the final string
    return str;
  }
  else
  {
    // Return an empty string for unsupported bases
    *str = 0;
    return str;
  }
}