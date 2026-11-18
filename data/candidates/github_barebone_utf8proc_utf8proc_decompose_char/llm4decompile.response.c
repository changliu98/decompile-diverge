utf8proc_ssize_t utf8proc_decompose_char(utf8proc_int32_t uc, utf8proc_int32_t *dst, utf8proc_ssize_t bufsize, utf8proc_option_t options, int *last_boundclass) {
  utf8proc_property_t *property;
  utf8proc_propval_t category;
  utf8proc_ssize_t hangul_tindex;
  utf8proc_ssize_t hangul_sindex;
  utf8proc_bool boundary;
  if (uc < 0 || uc >= 0x110000) {
    return -4;
  }
  property = unsafe_get_property(uc);
  category = property->category;
  hangul_tindex = uc - 0xac00;
  if ((options & (UTF8PROC_DECOMPOSE|UTF8PROC_COMPOSE)) &&
      hangul_tindex >= 0 &&
      hangul_tindex < 11172) {
    if (bufsize > 0) {
      dst[0] = 0x1100 + (hangul_tindex / 588);
    }
    if (bufsize > 1) {
      dst[1] = 0x1161 + ((hangul_tindex % 588) / 28);
    }
    if (hangul_tindex % 28) {
      if (bufsize > 2) {
        dst[2] = 0x11a7 + (hangul_tindex % 28);
      }
      return 3;
    }
    return 2;
  }
  if ((options & UTF8PROC_REJECTNA) && category == 0) {
    return -4;
  }
  if ((options & UTF8PROC_IGNORE) && property->ignorable) {
    return 0;
  }
  if ((options & UTF8PROC_STRIPNA) && category == 0) {
    return 0;
  }
  if ((options & UTF8PROC_LUMP)) {
    if (category == 23) {
      return utf8proc_decompose_char(0x20, dst, bufsize, options & ~UTF8PROC_LUMP, last_boundclass);
    }
    if (uc == 0x2018 || uc == 0x2019 || uc == 0x2c8 || uc == 0x640) {
      return utf8proc_decompose_char(0x27, dst, bufsize, options & ~UTF8PROC_LUMP, last_boundclass);
    }
    if (category == 13 || uc == 0x2212) {
      return utf8proc_decompose_char(0x2d, dst, bufsize, options & ~UTF8PROC_LUMP, last_boundclass);
    }
    if (uc == 0x2044 || uc == 0x2215) {
      return utf8proc_decompose_char(0x2f, dst, bufsize, options & ~UTF8PROC_LUMP, last_boundclass);
    }
    if (uc == 0x2236) {
      return utf8proc_decompose_char(0x3a, dst, bufsize, options & ~UTF8PROC_LUMP, last_boundclass);
    }
    if (uc == 0x2039 || uc == 0x2329 || uc == 0x3008) {
      return utf8proc_decompose_char(0x3c, dst, bufsize, options & ~UTF8PROC_LUMP, last_boundclass);
    }
    if (uc == 0x203a || uc == 0x232a || uc == 0x3009) {
      return utf8proc_decompose_char(0x3e, dst, bufsize, options & ~UTF8PROC_LUMP, last_boundclass);
    }
    if (uc == 0x2