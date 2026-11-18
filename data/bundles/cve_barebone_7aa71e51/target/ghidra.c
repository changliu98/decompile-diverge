u_char * smb_fdata(netdissect_options *ndo,u_char *buf,char *fmt,u_char *maxbuf,int unicodestr)

{
  char cVar1;
  u_char *puVar2;
  char *__s;
  char *pcVar3;
  long lVar4;
  size_t len;
  u_char *buf2;
  char *p;
  char s [128];
  int unicodestr_local;
  u_char *maxbuf_local;
  char *fmt_local;
  u_char *buf_local;
  netdissect_options *ndo_local;
  
  fmt_local = fmt;
  buf_local = buf;
  while( true ) {
    while( true ) {
      while( true ) {
        if (*fmt_local == '\0') {
          if ((smb_fdata::depth == 0) && (buf_local < maxbuf)) {
            lVar4 = (long)maxbuf - (long)buf_local;
            (*ndo->ndo_printf)(ndo,"Data: (%lu bytes)\n",lVar4);
            smb_print_data(ndo,buf_local,(int)lVar4);
            return buf_local + lVar4;
          }
          return buf_local;
        }
        cVar1 = *fmt_local;
        if (cVar1 == '#') {
          return buf_local;
        }
        if (cVar1 != '%') break;
        fmt_local = fmt_local + 1;
        buf_local = maxbuf;
      }
      if (cVar1 == '*') {
        puVar2 = buf_local;
        while( true ) {
          buf_local = puVar2;
          if (maxbuf <= buf_local) {
            return buf_local;
          }
          smb_fdata::depth = smb_fdata::depth + 1;
          puVar2 = smb_fdata(ndo,buf_local,fmt_local + 1,maxbuf,unicodestr);
          smb_fdata::depth = smb_fdata::depth + -1;
          if (puVar2 == (u_char *)0x0) break;
          if (puVar2 == buf_local) {
            return buf_local;
          }
        }
        return (u_char *)0x0;
      }
      if (cVar1 == '[') break;
      if (cVar1 == '|') {
        fmt_local = fmt_local + 1;
        if (maxbuf <= buf_local) {
          return buf_local;
        }
      }
      else {
        (*ndo->ndo_printf)(ndo,"%c",(ulong)(uint)(int)*fmt_local);
        fmt_local = fmt_local + 1;
      }
    }
    __s = fmt_local + 1;
    if (maxbuf <= buf_local) {
      return buf_local;
    }
    memset(s,0,0x80);
    pcVar3 = strchr(__s,0x5d);
    if ((char *)0x80 < pcVar3 + (1 - (long)__s)) break;
    strncpy(s,__s,(long)pcVar3 - (long)__s);
    pcVar3[(long)(s + -(long)__s)] = '\0';
    fmt_local = pcVar3 + 1;
    buf_local = smb_fdata1(ndo,buf_local,s,maxbuf,unicodestr);
    if (buf_local == (u_char *)0x0) {
      return (u_char *)0x0;
    }
  }
  return buf_local;
}