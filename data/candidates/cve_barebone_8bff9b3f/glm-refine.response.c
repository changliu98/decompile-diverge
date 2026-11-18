char *__cdecl bittok2str_internal(const tok *lp, const char *fmt, u_int v, const char *sep)
{
  int buflen = 0;
  const char *sepstr = "";

  // Iterate through the token array until a NULL string is encountered
  while (lp && lp->s)
  {
    // Iterate through all possible single-bit masks
    for (u_int rotbit = 1; rotbit != 0; rotbit <<= 1)
    {
      // If the token's value exactly matches a single bit extracted from 'v'
      if (lp->v == (rotbit & v))
      {
        buflen += snprintf(
            &bittok2str_internal_buf[buflen], 
            256 - buflen, 
            "%s%s", 
            sepstr, 
            lp->s
        );
        sepstr = sep;
        break;
      }
    }
    ++lp;
  }

  // If no bits matched, format the fallback string
  if (buflen == 0)
  {
    if (fmt)
      snprintf(bittok2str_internal_buf, 256, fmt, v);
    else
      snprintf(bittok2str_internal_buf, 256, "#%08x", v);
  }

  return bittok2str_internal_buf;
}