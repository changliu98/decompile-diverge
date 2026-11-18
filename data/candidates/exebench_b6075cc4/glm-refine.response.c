void __cdecl break_atr(char *str, char c)
{
  char *p = strrchr(str, c); // Find the last occurrence of 'c' in 'str'
  
  if (p)
    *p = '\0'; // Null-terminate the string at the found character
}