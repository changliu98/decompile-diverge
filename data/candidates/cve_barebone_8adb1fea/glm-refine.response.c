void __cdecl ga_concat_shorten_esc(garray_T *gap, char_u *str)
{
  char_u buf[65];
  int same_len;
  int clen;
  int c;
  char_u *s;
  char_u *p;

  if ( !str )
  {
    ga_concat(gap, (char_u *)"NULL");
    return;
  }

  for ( p = str; *p; ++p )
  {
    same_len = 1;
    s = p;
    c = mb_ptr2char_adv(&s);
    clen = (int)(s - p);

    while ( *s && c == (unsigned int)mb_ptr2char(s) )
    {
      ++same_len;
      s += clen;
    }

    if ( same_len <= 20 )
    {
      ga_concat_esc(gap, p, clen);
    }
    else
    {
      ga_concat(gap, (char_u *)"\\[");
      ga_concat_esc(gap, p, clen);
      ga_concat(gap, (char_u *)" occurs ");
      vim_snprintf((char *)buf, 65, "%d", same_len);
      ga_concat(gap, buf);
      ga_concat(gap, (char_u *)" times]");
      p = s - 1;
    }
  }
}