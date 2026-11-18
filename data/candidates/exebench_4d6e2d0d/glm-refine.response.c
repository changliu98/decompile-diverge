char *__cdecl str_cpy(char *dst, const char *src)
{
  char *dst_start = dst;

  do
  {
    *dst = *src;
    dst++;
  }
  while (*src++);

  return dst_start;
}