int __cdecl ellipsis(char *str, int len)
{
  char *ptr;
  bool inGBK;
  int i;
  int remaining;

  if (len < 0 || !str)
    return 0;

  if (len < 3)
  {
    str[len] = 0;
    return 1;
  }

  ptr = str;
  inGBK = false;

  // Iterate backwards from len - 3 to 0 to check for multi-byte characters
  for (i = len - 3; i != 0 && *ptr != 0; --i)
  {
    if (inGBK)
      inGBK = false;
    else
      inGBK = (*ptr < 0); // Equivalent to checking if the byte's high bit is set (>= 0x80)
    
    ++ptr;
  }

  // Skip the last 3 characters (or remaining characters if string ended early)
  remaining = 3;
  while (remaining > 0 && *ptr != 0)
  {
    ++ptr;
    --remaining;
  }

  // If the string hasn't reached its null terminator yet, we need to truncate and add ellipsis
  if (*ptr != 0)
  {
    if (remaining == 0)
    {
      str[len] = 0;
      ptr[-1] = '.';
      ptr[-2] = '.';
      
      // If we aren't currently in the middle of a GBK character, add the third dot
      if (!inGBK)
      {
        // Check if the character before the two dots is a GBK lead byte
        if ((ptr[-3] & 0x80) != 0)
          ptr[-3] = '.';
      }
    }
  }

  return 1;
}