void __cdecl msg_puts_printf(char_u *str, int maxlen)
{
  bool v2; // [rsp+7h] [rbp-39h]
  char_u *tofree; // [rsp+8h] [rbp-38h]
  int n; // [rsp+14h] [rbp-2Ch]
  char_u *p; // [rsp+18h] [rbp-28h]
  char_u *buf; // [rsp+20h] [rbp-20h]
  char_u *s; // [rsp+28h] [rbp-18h]

  s = str;
  p = str;
  while ( 1 )
  {
    if ( maxlen < 0 || (v2 = 0, (int)s - (int)str < maxlen) )
      v2 = *s != 0;
    if ( !v2 )
      break;
    if ( (!silent_mode || p_verbose) && *s == 10 )
    {
      n = (_DWORD)s - (_DWORD)p;
      buf = (char_u *)alloc((int)s - (int)p + 3);
      if ( buf )
      {
        memcpy(buf, p, n);
        if ( !info_message )
        {
          ++n;
          buf[(int)s - (int)p] = 13;
        }
        buf[n] = 10;
        buf[n + 1] = 0;
        if ( info_message )
          mch_msg((char *)buf);
        else
          mch_errmsg((char *)buf);
        vim_free(buf);
      }
      p = s + 1;
    }
    if ( *s == 13 || *s == 10 )
      msg_col = 0;
    else
      ++msg_col;
    ++s;
  }
  if ( *p && (!silent_mode || p_verbose) )
  {
    tofree = 0LL;
    if ( maxlen > 0 && strlen((const char *)p) > maxlen )
    {
      tofree = vim_strnsave(p, maxlen);
      p = tofree;
    }
    if ( p )
    {
      if ( info_message )
        mch_msg((char *)p);
      else
        mch_errmsg((char *)p);
      vim_free(tofree);
    }
  }
  msg_didout = 1;
}