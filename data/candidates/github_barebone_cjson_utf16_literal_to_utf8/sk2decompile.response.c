static unsigned char utf16_literal_to_utf8(const unsigned char *in,
                                           const unsigned char *in_end,
                                           unsigned char **out) {
  unsigned int c;
  unsigned char first_byte_mask = 0;
  unsigned char in_len;
  unsigned char i;
  unsigned char out_len;
  unsigned long ucs4;
  if (in_end - in < 6) return 0;
  c = parse_hex4(in + 2);
  if (c >= 0xd800 && c <= 0xdfff) return 0;
  if (c >= 0xdc00 || c < 0xd800) {
    in_len = 6;
    ucs4 = c;
  } else {
    in_len = 12;
    if (in_end - (in + 6) < 6) return 0;
    if (in[6] != '\\') return 0;
    if (in[7] != 'u') return 0;
    c = parse_hex4(in + 8);
    if (c < 0xd800 || c > 0xdfff) return 0;
    ucs4 = (((c & 0x3ff) << 10) | (c & 0x3ff)) + 0x10000;
  }
  if (ucs4 < 0x80) {
    out_len = 1;
  } else if (ucs4 < 0x800) {
    out_len = 2;
    first_byte_mask = 0xc0;
  } else if (ucs4 < 0x10000) {
    out_len = 3;
    first_byte_mask = 0xe0;
  } else if (ucs4 <= 0x10ffff) {
    out_len = 4;
    first_byte_mask = 0xf0;
  } else {
    return 0;
  }
  for (i = out_len - 1; i > 0; i--) {
    (*out)[i] = (ucs4 & 0x3f) | 0x80;
    ucs4 >>= 6;
  }
  if (out_len > 1)
    (*out)[0] = ucs4 | first_byte_mask;
  else
    (*out)[0] = ucs4 & 0x7f;
  *out += out_len;
  return in_len;
}