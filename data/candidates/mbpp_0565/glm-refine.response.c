char *__cdecl func0(char *src, char *dst)
{
  size_t length = strlen(src);
  memcpy(dst, src, length);
  dst[length] = '\0';
  return dst;
}