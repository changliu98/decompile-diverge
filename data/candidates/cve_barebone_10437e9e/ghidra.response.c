BITCODE_TU bit_utf8_to_TU(char *str,uint cquoted)

{
  size_t sVar1;
  char *pcVar2;
  bool bVar3;
  uchar c;
  size_t len;
  size_t i;
  BITCODE_TU wstr;
  uint cquoted_local;
  char *str_local;
  BITCODE_TU local_10;
  
  i = 0;
  len = strlen(str);
  if (0xfffe < len) {
    loglevel = 1;
    len = 0xfffe;
  }
  local_10 = calloc(2,len + 1);
  sVar1 = len;
  str_local = str;
  if (local_10 == (BITCODE_TU)0x0) {
    loglevel = 1;
    local_10 = (BITCODE_TU)0x0;
  }
  else {
    while( true ) {
      len = sVar1;
      bVar3 = false;
      if (len != 0) {
        c = *str_local;
        bVar3 = c != '\0';
        str_local = str_local + 1;
      }
      if (!bVar3) break;
      sVar1 = len - 1;
      if (c < 0x80) {
        if ((((cquoted == 0) || (c != '\\')) || (sVar1 < 2)) ||
           (((*str_local != '\"' && (*str_local != '\\')) &&
            ((*str_local != 'r' && (*str_local != 'n')))))) {
          local_10[i] = (ushort)c;
        }
        else {
          pcVar2 = str_local + 1;
          c = *str_local;
          str_local = pcVar2;
          if (c == 0x72) {
            local_10[i] = 0xd;
          }
          else if (c == 0x6e) {
            local_10[i] = 10;
          }
          else {
            local_10[i] = (ushort)c;
          }
        }
        i = i + 1;
      }
      else if ((c & 0xe0) == 0xc0) {
        if (sVar1 != 0) {
          local_10[i] = (c & 0x1f) << 6 | (short)str_local[1] & 0x3fU;
          i = i + 1;
        }
        str_local = str_local + 1;
        sVar1 = len - 2;
      }
      else if ((c & 0xf0) == 0xe0) {
        if (1 < sVar1) {
          local_10[i] = (ushort)c << 0xc | ((short)str_local[1] & 0x3fU) << 6 |
                        (short)str_local[2] & 0x3fU;
          i = i + 1;
        }
        str_local = str_local + 2;
        sVar1 = len - 3;
      }
    }
  }
  return local_10;
}