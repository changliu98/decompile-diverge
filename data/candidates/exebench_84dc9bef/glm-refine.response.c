void __cdecl trim(char *str)
{
  // Find the null terminator by advancing the pointer until it points to '\0'
  char *p = str;
  while (*p) 
    p++;

  // Overwrite the last character before the null terminator with '\0'
  p[-1] = 0;
}