int name_len(netdissect_options *ndo,uchar *s,uchar *maxbuf)

{
  uchar c;
  uchar *s0;
  uchar *maxbuf_local;
  uchar *s_local;
  netdissect_options *ndo_local;
  int local_c;
  
  if (s < maxbuf) {
    if ((ndo->ndo_snapend < ndo->ndo_snapend + -1) || (ndo->ndo_snapend + -1 < s)) {
LAB_0010152b:
      local_c = -1;
    }
    else {
      s_local = s;
      if ((*s & 0xc0) == 0xc0) {
        local_c = 2;
      }
      else {
        for (; *s_local != '\0'; s_local = s_local + (int)(*s_local + 1)) {
          if (maxbuf <= s_local) {
            return -1;
          }
          if ((ndo->ndo_snapend < ndo->ndo_snapend + -1) || (ndo->ndo_snapend + -1 < s_local))
          goto LAB_0010152b;
        }
        local_c = ((int)s_local - (int)s) + 1;
      }
    }
  }
  else {
    local_c = -1;
  }
  return local_c;
}