uint utf8_decode_v2(char *utf8char,size_t size,size_t *charlen)

{
  size_t *charlen_local;
  size_t size_local;
  char *utf8char_local;
  uint local_c;
  
  if ((size == 0) || (*utf8char == '\0')) {
    if (charlen != (size_t *)0x0) {
      *charlen = 0;
    }
    local_c = 0xffffffff;
  }
  else if (((int)*utf8char & 0x80U) == 0) {
    if (charlen != (size_t *)0x0) {
      *charlen = 1;
    }
    local_c = (int)*utf8char & 0x7f;
  }
  else if (((int)*utf8char & 0xe0U) == 0xc0) {
    if (charlen != (size_t *)0x0) {
      *charlen = 2;
    }
    if ((size < 2) || (utf8char[1] == '\0')) {
      local_c = 0xffffffff;
    }
    else {
      local_c = ((int)*utf8char & 0x1fU) << 6 | (int)utf8char[1] & 0x3fU;
    }
  }
  else if (((int)*utf8char & 0xf0U) == 0xe0) {
    if (charlen != (size_t *)0x0) {
      *charlen = 3;
    }
    if (((size < 3) || (utf8char[1] == '\0')) || (utf8char[2] == '\0')) {
      local_c = 0xffffffff;
    }
    else {
      local_c = ((int)*utf8char & 0xfU) << 0xc | ((int)utf8char[1] & 0x3fU) << 6 |
                (int)utf8char[2] & 0x3fU;
    }
  }
  else if (((int)*utf8char & 0xf8U) == 0xf0) {
    if (charlen != (size_t *)0x0) {
      *charlen = 4;
    }
    if ((((size < 4) || (utf8char[1] == '\0')) || (utf8char[2] == '\0')) || (utf8char[3] == '\0')) {
      local_c = 0xffffffff;
    }
    else {
      local_c = ((int)*utf8char & 7U) << 0xf | ((int)utf8char[1] & 0x3fU) << 0xc |
                ((int)utf8char[2] & 0x3fU) << 6 | (int)utf8char[3] & 0x3fU;
    }
  }
  else {
    if (charlen != (size_t *)0x0) {
      *charlen = 0;
    }
    local_c = 0xffffffff;
  }
  return local_c;
}