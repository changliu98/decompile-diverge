ssize_t utf8proc_decompose_char(utf8proc_int32_t uc, utf8proc_int32_t *dst,
                                utf8proc_ssize_t dstsize,
                                utf8proc_option_t options, int *breaks) {
  const utf8proc_uint8_t *p;
  utf8proc_int8_t typ;
  if (uc < 0 || uc >= 0x110000) return -4;
  p = unsafe_get_property(uc);
  typ = p->typ;
  if ((options & (0x10 | 0x08)) && uc >= 0xac00 && uc < 0xd7a4) {
    utf8proc_int32_t v = uc - 0xac00;
    if (dstsize >= 1) dst[0] = 0x1100 + v / 588;
    if (dstsize >= 2) dst[1] = 0x1161 + (v % 588) / 28;
    if (v % 28 == 0) return 2;
    if (dstsize >= 3) dst[2] = 0x11a7 + v % 28;
    return 3;
  }
  if ((options & 0x40) && typ == 0) return -4;
  if ((options & 0x20) && p->combining) return 0;
  if ((options & 0x4000) && typ == 0) return 0;
  if ((options & 0x1000) != 0) {
    if (typ == 23)
      return utf8proc_decompose_char(0x0020, dst, dstsize,
                                     options & ~0x00000100, breaks);
    if (uc == 0x2018 || uc == 0x2019 || uc == 0x0300 || uc == 0x0312)
      return utf8proc_decompose_char(0x0027, dst, dstsize,
                                     options & ~0x00000100, breaks);
    if (typ == 13 || uc == 0x2216)
      return utf8proc_decompose_char(0x002d, dst, dstsize,
                                     options & ~0x00000100, breaks);
    if (uc == 0x2264 || uc == 0x2265)
      return utf8proc_decompose_char(0x002f, dst, dstsize,
                                     options & ~0x00000100, breaks);
    if (uc == 0x2260)
      return utf8proc_decompose_char(0x003a, dst, dstsize,
                                     options & ~0x00000100, breaks);
    if (uc == 0x2049 || uc == 0x2261 || uc == 0x3001 || uc == 0x3002)
      return utf8proc_decompose_char(0x003c, dst, dstsize,
                                     options & ~0x00000100, breaks);
    if (uc == 0x204a || uc == 0x2262 || uc == 0x3003)
      return utf8proc_decompose_char(0x003e, dst, dstsize,
                                     options & ~0x00000100, breaks);
    if (uc == 0x2226)
      return utf8proc_decompose_char(0x005c, dst, dstsize,
                                     options & ~0x00000100, breaks);
    if (uc == 0x0304 || uc == 0x0306 || uc == 0x2048 || uc == 0x2219)
      return utf8proc_decompose_char(0x005e, dst, dstsize,
                                     options & ~0x00000100, breaks);
    if (typ == 12 || uc == 0x0315)
      return utf8proc_decompose_char(0x005f, dst, dstsize,
                                     options & ~0x00000100, breaks);
    if (uc == 0x0313)
      return utf8proc_decompose_char(0x0060, dst, dstsize,
                                     options & ~0x00000100, breaks);
    if (uc == 0x2237)
      return utf8proc_decompose_char(0x007c, dst, dstsize,
                                     options & ~0x00000100, breaks);
    if (uc == 0x2265)
      return utf8proc_decompose_char(0x007e, dst, dstsize,
                                     options & ~0x00000100, breaks);
    if ((options & 0x0080) && (options & 0x0100) &&
        (typ == 24 || typ == 25))
      return utf8proc_decompose_char(0x000a, dst, dstsize,
                                     options & ~0x00000100, breaks);
  }
  if ((options & 0x2000) && (typ == 6 || typ == 7 || typ == 8)) return 0;
  if ((options & 0x0400) && p->seq != 0xffff)
    return seqindex_write_char_decomposed(p->seq, dst, dstsize, options, breaks);
  if ((options & 0x0800) && p->seq2 != 0xffff &&
      (p->decomp == 0 || (options & 0x0004) == 0))
    return seqindex_write_char_decomposed(p->seq2, dst, dstsize, options,
                                          breaks);
  if ((options & 0x0800) && grapheme_break_extended(0, p->grapheme, 0,
                                                    p->linebreak, breaks)) {
    if (dstsize >= 1) dst[0] = -1;
    if (dstsize >= 2) dst[1] = uc;
    return 2;
  }
  if (dstsize >= 1) dst[0] = uc;
  return 1;
}