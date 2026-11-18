int __cdecl func0(char *(*dict)[2], int count)
{
  char *key;
  int i, j;
  bool has_upper, has_lower;

  if (!count)
    return 0;

  has_lower = false;
  has_upper = false;

  for (i = 0; i < count; ++i)
  {
    key = dict[i][0]; // Equivalent to (*dict)[2 * i]
    
    for (j = 0; key[j]; ++j)
    {
      // 0x400 corresponds to the _ISalpha flag in glibc
      if (!isalpha((unsigned char)key[j]))
        return 0;
        
      // 0x100 corresponds to the _ISupper flag
      if (isupper((unsigned char)key[j]))
        has_upper = true;
        
      // 0x200 corresponds to the _ISlower flag
      if (islower((unsigned char)key[j]))
        has_lower = true;

      // Equivalent to (has_lower + has_upper == 2)
      if (has_lower && has_upper)
        return 0;
    }
  }
  
  return 1;
}