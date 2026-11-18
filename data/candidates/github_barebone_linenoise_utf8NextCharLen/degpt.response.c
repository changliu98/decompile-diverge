size_t utf8NextCharLen(char *buf,size_t pos,size_t len)

{
  uint32_t cp_00;
  int iVar1;
  uint32_t nextcp;
  size_t nextlen;
  int isRI;
  uint32_t cp;
  size_t cplen;
  size_t curpos;
  size_t total;
  size_t len_local;
  size_t pos_local;
  char *buf_local;
  size_t local_10;
  
  if (pos < len) {
    total = 0;
    curpos = pos;
    len_local = len;
    pos_local = pos;
    buf_local = buf;
    cp = utf8DecodeChar(buf + pos,&cplen);
    total = cplen + total;
    curpos = cplen + curpos;
    isRI = isRegionalIndicator(cp);
    while (curpos < len_local) {
      cp_00 = utf8DecodeChar(buf_local + curpos,&nextlen);
      iVar1 = isZWJ(cp_00);
      if ((iVar1 == 0) || (len_local <= curpos + nextlen)) {
        iVar1 = isGraphemeExtend(cp_00);
        if (iVar1 == 0) {
          if ((isRI == 0) || (iVar1 = isRegionalIndicator(cp_00), iVar1 == 0)) break;
          total = nextlen + total;
          curpos = nextlen + curpos;
          isRI = 0;
        }
        else {
          total = nextlen + total;
          curpos = nextlen + curpos;
        }
      }
      else {
        total = nextlen + total;
        curpos = nextlen + curpos;
        utf8DecodeChar(buf_local + curpos,&nextlen);
        total = nextlen + total;
        curpos = nextlen + curpos;
      }
    }
    local_10 = total;
  }
  else {
    local_10 = 0;
  }
  return local_10;
}