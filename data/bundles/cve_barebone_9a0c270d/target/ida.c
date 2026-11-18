void __cdecl trunc_string(char_u *s, char_u *buf, int room_in, int buflen)
{
  int v4; // eax
  int v5; // eax
  char_u *v6; // rax
  bool v7; // [rsp+16h] [rbp-4Ah]
  bool v8; // [rsp+17h] [rbp-49h]
  size_t v9; // [rsp+18h] [rbp-48h]
  bool v10; // [rsp+23h] [rbp-3Dh]
  int n; // [rsp+24h] [rbp-3Ch]
  int na; // [rsp+24h] [rbp-3Ch]
  int nb; // [rsp+24h] [rbp-3Ch]
  int i; // [rsp+28h] [rbp-38h]
  int e; // [rsp+2Ch] [rbp-34h]
  size_t len; // [rsp+30h] [rbp-30h]
  unsigned __int64 lena; // [rsp+30h] [rbp-30h]
  __int64 lenb; // [rsp+30h] [rbp-30h]
  size_t lenc; // [rsp+30h] [rbp-30h]
  size_t half; // [rsp+38h] [rbp-28h]
  size_t halfa; // [rsp+38h] [rbp-28h]
  size_t room; // [rsp+40h] [rbp-20h]

  room = room_in - 3;
  len = 0LL;
  if ( *s )
  {
    if ( room_in < 3 )
      room = 0LL;
    half = room >> 1;
    for ( e = 0; ; ++e )
    {
      v10 = 0;
      if ( len < half )
        v10 = e < buflen;
      if ( !v10 )
        break;
      if ( !s[e] )
      {
        buf[e] = 0;
        return;
      }
      n = ptr2cells(&s[e]);
      if ( n + len > half )
        break;
      len += n;
      buf[e] = s[e];
      if ( has_mbyte )
      {
        n = mb_ptr2len(&s[e]);
        while ( --n > 0 )
        {
          if ( ++e == buflen )
            break;
          buf[e] = s[e];
        }
      }
    }
    i = e;
    if ( enc_dbcs )
    {
      na = vim_strsize(&s[e]);
      while ( na + len > room )
      {
        na -= ptr2cells(&s[i]);
        i += mb_ptr2len(&s[i]);
      }
    }
    else if ( enc_utf8 )
    {
      i = strlen((const char *)s);
      for ( halfa = i; ; i = halfa )
      {
        do
        {
          v9 = halfa;
          v4 = utf_head_off(s, &s[halfa - 1]);
          halfa = halfa - v4 - 1;
          v8 = 0;
          if ( v9 - v4 != 1 )
          {
            v5 = utf_ptr2char(&s[halfa]);
            v8 = utf_iscomposing(v5) != 0;
          }
        }
        while ( v8 );
        nb = ptr2cells(&s[halfa]);
        if ( nb + len > room || !halfa )
          break;
        len += nb;
      }
    }
    else
    {
      for ( i = strlen((const char *)s); ; --i )
      {
        v7 = 0;
        if ( i - 1 >= 0 )
        {
          n = ptr2cells(&s[i - 1]);
          v7 = n + len <= room;
        }
        if ( !v7 )
          break;
        len += n;
      }
    }
    if ( i > e + 3 )
    {
      if ( e + 3 >= buflen )
      {
        buf[e - 1] = 0;
      }
      else
      {
        v6 = &buf[e];
        v6[2] = 46;
        *(_WORD *)v6 = 11822;
        lenc = strlen((const char *)&s[i]) + 1;
        if ( lenc >= buflen - (__int64)e - 3 )
          lenc = buflen - e - 4;
        memmove(&buf[e + 3], &s[i], lenc);
        buf[lenc + 2 + e] = 0;
      }
    }
    else if ( s != buf )
    {
      lena = strlen((const char *)s);
      if ( lena >= buflen )
        lena = buflen - 1;
      lenb = lena - e + 1;
      if ( lenb )
        memmove(&buf[e], &s[e], lenb);
      else
        buf[e - 1] = 0;
    }
  }
  else if ( buflen > 0 )
  {
    *buf = 0;
  }
}