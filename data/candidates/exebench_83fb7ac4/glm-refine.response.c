char *__cdecl stringCopy(char *s, const char *t)
{
  while (*t)
  {
    *s++ = *t++;
  }
  
  *s = '\0';
  return s;
}