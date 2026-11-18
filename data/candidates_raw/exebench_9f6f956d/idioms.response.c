int strncpy(char *dest, char *src, int len)
{
  int i;
  int copy;
  if (len < 1 || !src || !dest) {
    if (dest)
      dest[0] = '\0';
    return 0;
  }
  for (i = 0; ; i++) {
    copy = 0;
    if (src[i])
      copy = i < len - 1 ? 1 : 0;
    if (!copy)
      break;
    dest[i] = src[i];
  }
  dest[i] = '\0';
  return i;
}