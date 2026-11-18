int __cdecl cpy(char *dst, char *src)
{
  int i;

  for (i = 0; i < 100 && src[i] != '\0'; ++i)
  {
    dst[i] = src[i];
  }
  
  dst[i] = '\0';
  return 0;
}