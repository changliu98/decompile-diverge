const u_char *__cdecl smb_fdata(
        netdissect_options *ndo,
        const u_char *buf,
        const char *fmt,
        const u_char *maxbuf,
        int unicodestr)
{
  int v6; // [rsp+4h] [rbp-CCh]
  size_t len; // [rsp+8h] [rbp-C8h]
  const u_char *buf2; // [rsp+10h] [rbp-C0h]
  char *p; // [rsp+18h] [rbp-B8h]
  char s[128]; // [rsp+20h] [rbp-B0h] BYREF
  int unicodestra; // [rsp+A4h] [rbp-2Ch]
  const u_char *maxbufa; // [rsp+A8h] [rbp-28h]
  const char *fmta; // [rsp+B0h] [rbp-20h]
  const u_char *bufa; // [rsp+B8h] [rbp-18h]
  netdissect_options *ndoa; // [rsp+C0h] [rbp-10h]

  ndoa = ndo;
  bufa = buf;
  fmta = fmt;
  maxbufa = maxbuf;
  unicodestra = unicodestr;
  while ( 1 )
  {
    while ( 1 )
    {
      if ( !*fmta )
      {
        if ( smb_fdata_depth || bufa >= maxbufa )
          return bufa;
        len = maxbufa - bufa;
        ndoa->ndo_printf(ndoa, "Data: (%lu bytes)\n", maxbufa - bufa);
        smb_print_data(ndoa, bufa, len);
        return &bufa[len];
      }
      v6 = *fmta;
      if ( v6 == 35 )
      {
        ++fmta;
        return bufa;
      }
      if ( v6 != 37 )
        break;
      ++fmta;
      bufa = maxbufa;
    }
    if ( v6 == 42 )
      break;
    if ( v6 == 91 )
    {
      ++fmta;
      if ( bufa >= maxbufa )
        return bufa;
      memset(s, 0, sizeof(s));
      p = strchr(fmta, 93);
      if ( (unsigned __int64)(p - fmta + 1) > 0x80 )
        return bufa;
      strncpy(s, fmta, p - fmta);
      s[p - fmta] = 0;
      fmta = p + 1;
      bufa = smb_fdata1(ndoa, bufa, s, maxbufa, unicodestra);
      if ( !bufa )
        return 0LL;
    }
    else if ( v6 == 124 )
    {
      ++fmta;
      if ( bufa >= maxbufa )
        return bufa;
    }
    else
    {
      ndoa->ndo_printf(ndoa, &unk_2004, (unsigned int)*fmta++);
    }
  }
  ++fmta;
  while ( bufa < maxbufa )
  {
    ++smb_fdata_depth;
    buf2 = smb_fdata(ndoa, bufa, fmta, maxbufa, unicodestra);
    --smb_fdata_depth;
    if ( !buf2 )
      return 0LL;
    if ( buf2 == bufa )
      return bufa;
    bufa = buf2;
  }
  return bufa;
}