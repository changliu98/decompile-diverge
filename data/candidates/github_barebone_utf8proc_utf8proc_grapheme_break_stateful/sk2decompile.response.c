utf8proc_bool utf8proc_grapheme_break_stateful(utf8proc_int32_t uc,
                                               utf8proc_int32_t last,
                                               utf8proc_int32_t *state) {
  const utf8proc_uint8_t *p = utf8proc_get_property(uc);
  const utf8proc_uint8_t *lp = utf8proc_get_property(last);
  return grapheme_break_extended((p[3] & 0x3f00) >> 8, (lp[3] & 0x3f00) >> 8,
                                 p[3] >> 30, lp[3] >> 30, state);
}