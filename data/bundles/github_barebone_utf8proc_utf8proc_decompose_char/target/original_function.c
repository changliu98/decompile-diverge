UTF8PROC_DLLEXPORT utf8proc_ssize_t utf8proc_decompose_char(utf8proc_int32_t uc, utf8proc_int32_t *dst, utf8proc_ssize_t bufsize, utf8proc_option_t options, int *last_boundclass) {
  const utf8proc_property_t *property;
  utf8proc_propval_t category;
  utf8proc_int32_t hangul_sindex;
  if (uc < 0 || uc >= 0x110000) return UTF8PROC_ERROR_NOTASSIGNED;
  property = unsafe_get_property(uc);
  category = property->category;
  hangul_sindex = uc - UTF8PROC_HANGUL_SBASE;
  if (options & (UTF8PROC_COMPOSE|UTF8PROC_DECOMPOSE)) {
    if (hangul_sindex >= 0 && hangul_sindex < UTF8PROC_HANGUL_SCOUNT) {
      utf8proc_int32_t hangul_tindex;
      if (bufsize >= 1) {
        dst[0] = UTF8PROC_HANGUL_LBASE +
          hangul_sindex / UTF8PROC_HANGUL_NCOUNT;
        if (bufsize >= 2) dst[1] = UTF8PROC_HANGUL_VBASE +
          (hangul_sindex % UTF8PROC_HANGUL_NCOUNT) / UTF8PROC_HANGUL_TCOUNT;
      }
      hangul_tindex = hangul_sindex % UTF8PROC_HANGUL_TCOUNT;
      if (!hangul_tindex) return 2;
      if (bufsize >= 3) dst[2] = UTF8PROC_HANGUL_TBASE + hangul_tindex;
      return 3;
    }
  }
  if (options & UTF8PROC_REJECTNA) {
    if (!category) return UTF8PROC_ERROR_NOTASSIGNED;
  }
  if (options & UTF8PROC_IGNORE) {
    if (property->ignorable) return 0;
  }
  if (options & UTF8PROC_STRIPNA) {
    if (!category) return 0;
  }
  if (options & UTF8PROC_LUMP) {
    if (category == UTF8PROC_CATEGORY_ZS) utf8proc_decompose_lump(0x0020);
    if (uc == 0x2018 || uc == 0x2019 || uc == 0x02BC || uc == 0x02C8)
      utf8proc_decompose_lump(0x0027);
    if (category == UTF8PROC_CATEGORY_PD || uc == 0x2212)
      utf8proc_decompose_lump(0x002D);
    if (uc == 0x2044 || uc == 0x2215) utf8proc_decompose_lump(0x002F);
    if (uc == 0x2236) utf8proc_decompose_lump(0x003A);
    if (uc == 0x2039 || uc == 0x2329 || uc == 0x3008)
      utf8proc_decompose_lump(0x003C);
    if (uc == 0x203A || uc == 0x232A || uc == 0x3009)
      utf8proc_decompose_lump(0x003E);
    if (uc == 0x2216) utf8proc_decompose_lump(0x005C);
    if (uc == 0x02C4 || uc == 0x02C6 || uc == 0x2038 || uc == 0x2303)
      utf8proc_decompose_lump(0x005E);
    if (category == UTF8PROC_CATEGORY_PC || uc == 0x02CD)
      utf8proc_decompose_lump(0x005F);
    if (uc == 0x02CB) utf8proc_decompose_lump(0x0060);
    if (uc == 0x2223) utf8proc_decompose_lump(0x007C);
    if (uc == 0x223C) utf8proc_decompose_lump(0x007E);
    if ((options & UTF8PROC_NLF2LS) && (options & UTF8PROC_NLF2PS)) {
      if (category == UTF8PROC_CATEGORY_ZL ||
          category == UTF8PROC_CATEGORY_ZP)
        utf8proc_decompose_lump(0x000A);
    }
  }
  if (options & UTF8PROC_STRIPMARK) {
    if (category == UTF8PROC_CATEGORY_MN ||
      category == UTF8PROC_CATEGORY_MC ||
      category == UTF8PROC_CATEGORY_ME) return 0;
  }
  if (options & UTF8PROC_CASEFOLD) {
    if (property->casefold_seqindex != UINT16_MAX) {
      return seqindex_write_char_decomposed(property->casefold_seqindex, dst, bufsize, options, last_boundclass);
    }
  }
  if (options & (UTF8PROC_COMPOSE|UTF8PROC_DECOMPOSE)) {
    if (property->decomp_seqindex != UINT16_MAX &&
        (!property->decomp_type || (options & UTF8PROC_COMPAT))) {
      return seqindex_write_char_decomposed(property->decomp_seqindex, dst, bufsize, options, last_boundclass);
    }
  }
  if (options & UTF8PROC_CHARBOUND) {
    utf8proc_bool boundary;
    boundary = grapheme_break_extended(0, property->boundclass, 0, property->indic_conjunct_break,
                                       last_boundclass);
    if (boundary) {
      if (bufsize >= 1) dst[0] = -1; /* sentinel value for grapheme break */
      if (bufsize >= 2) dst[1] = uc;
      return 2;
    }
  }
  if (bufsize >= 1) *dst = uc;
  return 1;
}