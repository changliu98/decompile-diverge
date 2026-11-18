int Utf8ToUnicode(char *utf8char,int *unicode,int *len,size_t leaveLen)

{
  char cVar1;
  char cTmp;
  size_t leaveLen_local;
  int *len_local;
  int *unicode_local;
  char *utf8char_local;
  
  cVar1 = *utf8char;
  if (((int)cVar1 & 0xf8U) == 0xf0) {
    if (((leaveLen < 4) || (((int)utf8char[1] & 0xc0U) != 0x80)) ||
       ((((int)utf8char[2] & 0xc0U) != 0x80 || (((int)utf8char[3] & 0xc0U) != 0x80)))) {
      return 2;
    }
    *len = 4;
    *unicode = (int)cVar1 & 7U | *unicode;
    *unicode = *unicode << 6;
    *unicode = (int)utf8char[1] & 0x3fU | *unicode;
    *unicode = *unicode << 6;
    *unicode = (int)utf8char[2] & 0x3fU | *unicode;
    *unicode = *unicode << 6;
    *unicode = (int)utf8char[3] & 0x3fU | *unicode;
  }
  else if (((int)cVar1 & 0xf0U) == 0xe0) {
    if (((leaveLen < 3) || (((int)utf8char[1] & 0xc0U) != 0x80)) ||
       (((int)utf8char[2] & 0xc0U) != 0x80)) {
      return 2;
    }
    *len = 3;
    *unicode = (int)cVar1 & 0xfU | *unicode;
    *unicode = *unicode << 6;
    *unicode = (int)utf8char[1] & 0x3fU | *unicode;
    *unicode = *unicode << 6;
    *unicode = (int)utf8char[2] & 0x3fU | *unicode;
  }
  else if (((int)cVar1 & 0xe0U) == 0xc0) {
    if ((leaveLen < 2) || (((int)utf8char[1] & 0xc0U) != 0x80)) {
      return 2;
    }
    *len = 2;
    *unicode = (int)cVar1 & 0x1fU | *unicode;
    *unicode = *unicode << 6;
    *unicode = (int)utf8char[1] & 0x3fU | *unicode;
  }
  else {
    if (((int)cVar1 & 0x80U) != 0) {
      return 1;
    }
    *len = 1;
    *unicode = (int)cVar1;
  }
  return 0;
}