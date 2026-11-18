void __cdecl itoa(int dst, char *src)
{
  int udst; // [rsp+0h] [rbp-2Ch]
  char exc; // [rsp+Bh] [rbp-21h]
  char *str2; // [rsp+Ch] [rbp-20h]
  char *str1; // [rsp+14h] [rbp-18h]

  str1 = src;
  if ( dst >= 0 )
  {
    udst = dst;
  }
  else
  {
    udst = -dst;
    *src = 45;
    str1 = src + 1;
  }
  str2 = str1;
  do
  {
    *str2 = udst % 10 + 48;
    udst /= 10;
    ++str2;
  }
  while ( udst );
  *str2 = 0;
  while ( str1 < --str2 )
  {
    exc = *str1;
    *str1 = *str2;
    *str2 = exc;
    ++str1;
  }
}