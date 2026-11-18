char *__cdecl gdb_strcpy(char *buf, const char *s)
{
  char *original_buf = buf;

  while (*s)
  {
    *buf++ = *s++;
  }
  *buf = '\0';

  return original_buf;
}