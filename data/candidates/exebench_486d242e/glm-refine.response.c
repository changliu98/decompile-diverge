void __cdecl ck_encrypt(char *s)
{
  while (*s)
  {
    if (*s != 'p' && *s != '\\' && *s != 'S')
    {
      *s ^= 15;
    }
    s++;
  }
}