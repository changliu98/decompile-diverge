int __cdecl stringToInt(unsigned int *out_val, const char *str)
{
  unsigned int result = 0;
  const char *p = str;

  while (*p != '\0')
  {
    char c = *p;
    
    // Check if the character is outside the ASCII range for '0' to '9'
    if (c < '0' || c > '9')
      return -1;
      
    // Shift the current result by one decimal place and add the new digit.
    // The post-increment on the pointer advances it to the next character.
    result = (result * 10) + (c - '0');
    p++;
  }

  *out_val = result;
  return 0;
}