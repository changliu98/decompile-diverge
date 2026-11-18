unsigned int __cdecl str_copy(char *dest, const char *src)
{
  unsigned int len = 0;

  while (1)
  {
    // 1st byte
    dest[0] = src[0];
    if (!src[0]) return len;
    len++;

    // 2nd byte
    dest[1] = src[1];
    if (!src[1]) return len;
    len++;

    // 3rd byte
    dest[2] = src[2];
    if (!src[2]) return len;
    len++;

    // 4th byte
    dest[3] = src[3];
    if (!src[3]) break;

    dest += 4;
    src += 4;
    len++;
  }

  return len;
}