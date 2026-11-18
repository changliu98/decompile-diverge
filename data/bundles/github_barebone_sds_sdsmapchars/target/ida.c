sds __cdecl sdsmapchars(sds s, const char *from, const char *to, size_t setlen)
{
  size_t l; // [rsp+8h] [rbp-38h]
  size_t i; // [rsp+10h] [rbp-30h]
  size_t j; // [rsp+18h] [rbp-28h]

  l = sdslen(s);
  for ( j = 0LL; j < l; ++j )
  {
    for ( i = 0LL; i < setlen; ++i )
    {
      if ( s[j] == from[i] )
      {
        s[j] = to[i];
        break;
      }
    }
  }
  return s;
}