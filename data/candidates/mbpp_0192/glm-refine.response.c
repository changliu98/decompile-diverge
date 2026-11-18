int __cdecl func0(const char *str)
{
  int has_lower = 0;
  int has_digit = 0;

  while (*str)
  {
    // 0x400 corresponds to the _ISlower flag in the glibc ctype bitmasks
    if (islower((unsigned char)*str))
      has_lower = 1;
      
    // 0x800 corresponds to the _ISdigit flag in the glibc ctype bitmasks
    if (isdigit((unsigned char)*str))
      has_digit = 1;
      
    ++str;
  }

  // Returns true if both a lowercase letter and a digit were found
  return has_lower && has_digit;
}