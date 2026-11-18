char * utf_16le_to_utf_8_truncated(wchar_t *utf_16,char *utf_8,size_t utf_8_len)

{
  wchar_t wVar1;
  byte bVar2;
  wchar_t *pwVar3;
  byte *pbVar4;
  uint32_t uc;
  wchar_t c2;
  wchar_t c;
  size_t utf_8_len_local;
  char *utf_8_local;
  wchar_t *utf_16_local;
  char *local_10;
  
  utf_8_len_local = utf_8_len;
  utf_8_local = utf_8;
  utf_16_local = utf_16;
  local_10 = utf_8;
  if (utf_8_len != 0) {
    while( true ) {
      pwVar3 = utf_16_local + 1;
      uc = *utf_16_local;
      if (uc == L'\0') break;
      if (((int)uc < L'\xd800') || (L'\xdbff' < (int)uc)) {
        utf_16_local = pwVar3;
        if ((L'\xdbff' < (int)uc) && ((int)uc < L'\xe000')) {
          uc = 0xfffd;
        }
      }
      else {
        wVar1 = *pwVar3;
        if (wVar1 == L'\0') {
          uc = 0xfffd;
          utf_16_local = pwVar3;
        }
        else {
          utf_16_local = utf_16_local + 2;
          if ((wVar1 < L'\xdc00') || (L'\xdfff' < wVar1)) {
            uc = 0xfffd;
          }
          else {
            uc = ((uc + L'\xffff2800') * 0x400 | wVar1 + L'\xffff2400') + 0x10000;
          }
        }
      }
      bVar2 = (byte)uc;
      if (uc < 0x80) {
        if (utf_8_len_local < 2) break;
        *utf_8_local = bVar2;
        utf_8_len_local = utf_8_len_local - 1;
        utf_8_local = utf_8_local + 1;
      }
      else if (uc < 0x800) {
        if (utf_8_len_local < 3) break;
        pbVar4 = (byte *)(utf_8_local + 1);
        *utf_8_local = (byte)(uc >> 6) & 0x3f | 0xc0;
        utf_8_local = utf_8_local + 2;
        *pbVar4 = bVar2 & 0x3f | 0x80;
        utf_8_len_local = utf_8_len_local - 2;
      }
      else {
        if (uc < 0x10000) {
          if (utf_8_len_local < 4) break;
          *utf_8_local = (byte)(uc >> 0xc) & 0xf | 0xe0;
          pbVar4 = (byte *)(utf_8_local + 2);
          utf_8_local[1] = (byte)(uc >> 6) & 0x3f | 0x80;
          utf_8_local = utf_8_local + 3;
          *pbVar4 = bVar2 & 0x3f | 0x80;
        }
        else {
          if (utf_8_len_local < 5) break;
          *utf_8_local = (byte)(uc >> 0x12) & 3 | 0xf0;
          utf_8_local[1] = (byte)(uc >> 0xc) & 0x3f | 0x80;
          pbVar4 = (byte *)(utf_8_local + 3);
          utf_8_local[2] = (byte)(uc >> 6) & 0x3f | 0x80;
          utf_8_local = utf_8_local + 4;
          *pbVar4 = bVar2 & 0x3f | 0x80;
        }
        utf_8_len_local = utf_8_len_local - 3;
      }
    }
    *utf_8_local = '\0';
    local_10 = utf_8_local;
  }
  return local_10;
}