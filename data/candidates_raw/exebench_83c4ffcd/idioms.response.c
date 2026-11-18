char *strlcpy(char *dst, char *src, int size)
{
  int i;
  for (i = 0; ; i++) {
    int should_copy = i < size - 1;
    if (!should_copy)
      break;
    should_copy = *src != '\0';
    if (!should_copy)
      break;
    should_copy = *src != '\n';
    if (!should_copy)
      break;
    should_copy = *src != '\r';
    if (!should_copy)
      break;
    *dst++ = *src++;
  }
  *dst = '\0';
  if (*src == '\r')
    src++;
  if (*src == '\n')
    src++;
  return src;
}