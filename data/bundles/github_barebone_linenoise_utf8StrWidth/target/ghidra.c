size_t utf8StrWidth(char *s,size_t len)

{
  uint32_t cp_00;
  int iVar1;
  size_t sVar2;
  size_t skip;
  uint32_t cp;
  size_t clen;
  int after_zwj;
  size_t i;
  size_t width;
  size_t len_local;
  char *s_local;
  
  width = 0;
  i = 0;
  after_zwj = 0;
  len_local = len;
  s_local = s;
  while (i < len_local) {
    cp_00 = utf8DecodeChar(s_local + i,&clen);
    if ((cp_00 == 0x1b) && (sVar2 = ansiEscapeLen(s_local + i,len_local - i), sVar2 != 0)) {
      i = sVar2 + i;
    }
    else {
      if (after_zwj == 0) {
        iVar1 = utf8CharWidth(cp_00);
        width = (long)iVar1 + width;
      }
      else {
        after_zwj = 0;
      }
      iVar1 = isZWJ(cp_00);
      if (iVar1 != 0) {
        after_zwj = 1;
      }
      i = clen + i;
    }
  }
  return width;
}