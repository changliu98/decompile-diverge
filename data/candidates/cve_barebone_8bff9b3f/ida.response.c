char *__cdecl bittok2str_internal(const tok *lp, const char *fmt, u_int v, const char *sep)
{
  bool v5; // [rsp+17h] [rbp-39h]
  const char *sepstr; // [rsp+18h] [rbp-38h]
  u_int rotbit; // [rsp+28h] [rbp-28h]
  int buflen; // [rsp+2Ch] [rbp-24h]

  buflen = 0;
  sepstr = "";
  while ( 1 )
  {
    v5 = 0;
    if ( lp )
      v5 = lp->s != 0LL;
    if ( !v5 )
      break;
    for ( rotbit = 1; rotbit; rotbit *= 2 )
    {
      if ( lp->v == (rotbit & v) )
      {
        buflen += snprintf(&bittok2str_internal_buf[buflen], 256LL - buflen, "%s%s", sepstr, lp->s);
        sepstr = sep;
        break;
      }
    }
    ++lp;
  }
  if ( !buflen )
  {
    if ( fmt )
      snprintf(bittok2str_internal_buf, 0x100uLL, fmt, v);
    else
      snprintf(bittok2str_internal_buf, 0x100uLL, "#%08x", v);
  }
  return bittok2str_internal_buf;
}