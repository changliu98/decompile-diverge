void copy_string(char *dst, char *src, int max)
{
  int i;
  for (i = 0; ; i++) {
    int done = 0;
    if (i < max)
      done = (dst[i] = src[i]) != '\0';
    if (!done)
      break;
  }
}