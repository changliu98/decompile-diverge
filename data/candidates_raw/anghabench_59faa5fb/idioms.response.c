void smb_sanitize(void *str, int len)
{
  int terminated = 0;
  unsigned char *ptr = (unsigned char *)str;
  while (len > 0) {
    if (*ptr == '\0')
      terminated = 1;
    if (terminated || *ptr < ' ' || *ptr > '~')
      *ptr = ' ';
    --len;
    ++ptr;
  }
}