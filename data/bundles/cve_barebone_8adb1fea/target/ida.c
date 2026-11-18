void __cdecl ga_concat_shorten_esc(garray_T *gap, char_u *str)
{
  int v2; // [rsp+4h] [rbp-7Ch]
  bool v3; // [rsp+Bh] [rbp-75h]
  int same_len; // [rsp+Ch] [rbp-74h]
  char_u buf[65]; // [rsp+10h] [rbp-70h] BYREF
  int clen; // [rsp+58h] [rbp-28h]
  int c; // [rsp+5Ch] [rbp-24h]
  char_u *s; // [rsp+60h] [rbp-20h] BYREF
  char_u *p; // [rsp+68h] [rbp-18h]
  char_u *stra; // [rsp+70h] [rbp-10h]
  garray_T *gapa; // [rsp+78h] [rbp-8h]

  gapa = gap;
  stra = str;
  if ( str )
  {
    for ( p = stra; *p; ++p )
    {
      same_len = 1;
      s = p;
      c = mb_ptr2char_adv(&s);
      for ( clen = (_DWORD)s - (_DWORD)p; ; s += clen )
      {
        v3 = 0;
        if ( *s )
        {
          v2 = c;
          v3 = v2 == (unsigned int)mb_ptr2char(s);
        }
        if ( !v3 )
          break;
        ++same_len;
      }
      if ( same_len <= 20 )
      {
        ga_concat_esc(gapa, p, clen);
      }
      else
      {
        ga_concat(gapa, (char_u *)"\\[");
        ga_concat_esc(gapa, p, clen);
        ga_concat(gapa, (char_u *)" occurs ");
        vim_snprintf((char *)buf, 0x41uLL, "%d", (unsigned int)same_len);
        ga_concat(gapa, buf);
        ga_concat(gapa, (char_u *)" times]");
        p = s - 1;
      }
    }
  }
  else
  {
    ga_concat(gapa, (char_u *)"NULL");
  }
}