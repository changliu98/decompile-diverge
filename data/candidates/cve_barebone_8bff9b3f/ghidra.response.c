char * bittok2str_internal(tok *lp,char *fmt,u_int v,char *sep)

{
  int iVar1;
  bool bVar2;
  char *local_50;
  char *sepstr;
  u_int tokval;
  u_int rotbit;
  int buflen;
  char *sep_local;
  u_int v_local;
  char *fmt_local;
  tok *lp_local;
  
  buflen = 0;
  sepstr = "";
  lp_local = lp;
  do {
    bVar2 = false;
    if (lp_local != (tok *)0x0) {
      bVar2 = lp_local->s != (char *)0x0;
    }
    if (!bVar2) {
      if (buflen == 0) {
        local_50 = fmt;
        if (fmt == (char *)0x0) {
          local_50 = "#%08x";
        }
        snprintf(bittok2str_internal::buf,0x100,local_50,(ulong)v);
      }
      return bittok2str_internal::buf;
    }
    for (rotbit = 1; rotbit != 0; rotbit = rotbit << 1) {
      if (lp_local->v == (v & rotbit)) {
        iVar1 = snprintf(bittok2str_internal::buf + buflen,0x100 - (long)buflen,"%s%s",sepstr,
                         lp_local->s);
        buflen = iVar1 + buflen;
        sepstr = sep;
        break;
      }
    }
    lp_local = lp_local + 1;
  } while( true );
}