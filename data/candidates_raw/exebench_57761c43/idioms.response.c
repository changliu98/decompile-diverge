void strreplace(char *str, char oldc, char newc)
{
  while (*str++)
    if (*str == oldc)
      *str = newc;
}