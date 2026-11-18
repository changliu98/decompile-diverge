void __cdecl set_nb(const char *s, char c, int *nb)
{
  int i2; // [rsp+0h] [rbp-20h]
  int i1; // [rsp+4h] [rbp-1Ch]

  i1 = 0;
  i2 = 0;
  while ( s[i1] )
  {
    if ( i1 == i2 && s[i1] == c )
    {
      ++i1;
      ++i2;
    }
    else if ( s[i2] != c && s[i2] )
    {
      ++i2;
    }
    else
    {
      ++*nb;
      i1 = i2;
    }
  }
}