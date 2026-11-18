char *__cdecl strcpy_x86_64_fast(char *dst, const char *src)
{
  char *original_dst = dst;
  char c;

  do
  {
    c = *src++;
    *dst++ = c;
  }
  while (c);

  return original_dst;
}