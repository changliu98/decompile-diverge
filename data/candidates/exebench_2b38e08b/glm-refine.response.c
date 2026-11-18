void __cdecl copy_string(char *dst, char *src, int max)
{
  int i;

  for (i = 0; i < max; ++i)
  {
    dst[i] = src[i];
    if (src[i] == '\0')
      break;
  }
}