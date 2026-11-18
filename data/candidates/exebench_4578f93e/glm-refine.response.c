char *__cdecl mystrncpy(char *dest, char *src, int n)
{
  char *desta = dest;
  int i;

  for (i = 0; i < n && *src != '\0'; ++i)
  {
    *desta++ = *src++;
  }
  
  *desta = '\0';
  return dest;
}