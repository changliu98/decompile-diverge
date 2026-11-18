void __cdecl sdsrange(sds s, ssize_t start, ssize_t end)
{
  ssize_t v3; // [rsp+0h] [rbp-30h]
  signed __int64 len; // [rsp+8h] [rbp-28h]
  size_t newlen; // [rsp+10h] [rbp-20h]
  ssize_t starta; // [rsp+20h] [rbp-10h]

  starta = start;
  len = sdslen(s);
  if ( len )
  {
    if ( start < 0 )
    {
      starta = start + len;
      if ( start + len < 0 )
        starta = 0LL;
    }
    if ( end < 0 )
    {
      end += len;
      if ( end < 0 )
        end = 0LL;
    }
    if ( starta <= end )
      v3 = end - starta + 1;
    else
      v3 = 0LL;
    newlen = v3;
    if ( v3 )
    {
      if ( starta < len )
      {
        if ( end >= len )
          newlen = len - starta;
      }
      else
      {
        newlen = 0LL;
      }
    }
    if ( starta )
    {
      if ( newlen )
        memmove(s, &s[starta], newlen);
    }
    s[newlen] = 0;
    sdssetlen(s, newlen);
  }
}