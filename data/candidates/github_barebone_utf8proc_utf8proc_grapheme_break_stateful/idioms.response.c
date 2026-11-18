int utf8proc_grapheme_break_stateful(int c1, int c2, int *state) {
  struct utf8proc_property *p1 = utf8proc_get_property(c1);
  struct utf8proc_property *p2 = utf8proc_get_property(c2);
  return grapheme_break_extended(p1->combining, p2->combining,
                                 p1->bidirectional, p2->bidirectional,
                                 state);
}