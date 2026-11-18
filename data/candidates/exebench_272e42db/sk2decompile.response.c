static void decode_mode10_short_delta(unsigned int delta, int *r, int *g,
                                      int *b) {
  *b = delta & 0x1f;
  if (*b & 0x10) *b |= 0xffffffe0;
  *b <<= 1;
  *g = (delta & 0x3e0) >> 5;
  if (*g & 0x10) *g |= 0xffffffe0;
  *r = (delta & 0x7c00) >> 10;
  if (*r & 0x10) *r |= 0xffffffe0;
}