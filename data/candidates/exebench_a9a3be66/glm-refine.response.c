void __cdecl byte2bits(char c, char *s)
{
  for (int i = 7; i >= 0; --i)
  {
    *s++ = ((c >> i) & 1) + '0';
  }
  *s = '\0';
}