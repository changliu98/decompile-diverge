void char_replace(char *str, char oldc, char newc)
{
  while (*str++)
    if (*str == oldc)
      *str = newc;
}