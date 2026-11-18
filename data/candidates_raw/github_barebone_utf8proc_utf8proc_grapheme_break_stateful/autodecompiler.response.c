int utf8proc_grapheme_break_stateful(int l, int r, void *state)
{
 const struct utf8proc_property *lprop = utf8proc_get_property(l);
 const struct utf8proc_property *rprop = utf8proc_get_property(r);

 return grapheme_break_extended(
  ((lprop->category >> 30) & 0x3),
  ((lprop->category >> 24) & 0x3F),
  ((rprop->category >> 30) & 0x3),
  ((rprop->category >> 24) & 0x3F),
  state) & 1;
}