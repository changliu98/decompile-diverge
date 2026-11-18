utf8proc_bool utf8proc_grapheme_break_stateful(utf8proc_int32_t c1, utf8proc_int32_t c2, utf8proc_int32_t *state) {
  const utf8proc_property_t *p1 = utf8proc_get_property(c1);
  const utf8proc_property_t *p2 = utf8proc_get_property(c2);
  return grapheme_break_extended(p1->boundclass, p2->boundclass, p1->indic_conjunct_break, p2->indic_conjunct_break, state);
}