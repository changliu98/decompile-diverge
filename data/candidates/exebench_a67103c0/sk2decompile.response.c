int unicoder_utf16_decode(unsigned int *codepoint, unsigned char *in,
                          int inlen) {
  unsigned int c1, c2;
  if (inlen != 2 && inlen != 1) return -4;
  if (in == NULL) return -1;
  if (codepoint == NULL) return -1;
  if (inlen == 1) {
    c1 = in[0] | (in[1] << 8);
    c2 = in[2] | (in[3] << 8);
  } else {
    c1 = in[1] | (in[0] << 8);
    c2 = in[3] | (in[2] << 8);
  }
  if (c1 >= 0xd800 && c1 <= 0xdbff) {
    if (c1 < 0xdc00) {
      if (c2 >= 0xdc00 && c2 <= 0xdfff) {
        *codepoint = 0;
        *codepoint |= (c1 & 0x03ff);
        *codepoint <<= 10;
        *codepoint |= (c2 & 0x03ff);
        *codepoint += 0x10000;
        return 4;
      } else {
        return -8;
      }
    } else {
      return -8;
    }
  } else if (c1 <= 0x10ffff) {
    *codepoint = c1;
    return 2;
  } else {
    return -16;
  }
}