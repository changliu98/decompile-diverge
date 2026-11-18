int strlcpy(char *dst, char *src, int size)
{
  if (size > 0) {
    --size;
    if (size > 0) {
      do {
        *dst++ = *src++;
      } while (*dst != '\0' && --size > 0);
    }
  }
  if (size == 0) {
    if (size > 0) {
      *dst = '\0';
    }
    while (*src++)
      ;
  }
  return (int)(src - (char *)src - 1);
}