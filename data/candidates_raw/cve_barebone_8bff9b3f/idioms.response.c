char *bittok2str(struct tok *tok, char *fmt, unsigned int v, char *sep)
{
  int buflen = 0;
  char *sepstr = "";
  for (;;) {
    unsigned int rotbit = 0;
    int hasstr = (tok ? (tok->s != ((void *)0)) : 0);
    if (!hasstr)
      break;
    for (rotbit = 1; rotbit; rotbit <<= 1)
      if (rotbit & v == rotbit) {
        buflen += xsnprintf(bittok2str_internal_buf + buflen,
                            sizeof(bittok2str_internal_buf) - buflen,
                            "%s%s", sepstr, tok->s);
        sepstr = sep;
        break;
      }
    tok++;
  }
  if (!buflen) {
    if (fmt)
      xsnprintf(bittok2str_internal_buf, sizeof(bittok2str_internal_buf),
                fmt, v);
    else
      xsnprintf(bittok2str_internal_buf, sizeof(bittok2str_internal_buf),
                "#%08x", v);
  }
  return bittok2str_internal_buf;
}