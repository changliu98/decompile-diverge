void __cdecl strcpy_(char *dst, const char *src)
{
  while (*src)
  {
    *dst++ = *src++;
  }
  *dst = '\0';
}