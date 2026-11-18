utf8proc_bool __cdecl utf8proc_grapheme_break_stateful(
        utf8proc_int32_t c1,
        utf8proc_int32_t c2,
        utf8proc_int32_t *state)
{
  const utf8proc_property_t *p2; // [rsp+0h] [rbp-20h]
  const utf8proc_property_t *p1; // [rsp+8h] [rbp-18h]

  p1 = utf8proc_get_property(c1);
  p2 = utf8proc_get_property(c2);
  return grapheme_break_extended(
           HIBYTE(*(_DWORD *)((char *)p1 + 18)) & 0x3F,
           HIBYTE(*(_DWORD *)((char *)p2 + 18)) & 0x3F,
           *(_DWORD *)((char *)p1 + 18) >> 30,
           *(_DWORD *)((char *)p2 + 18) >> 30,
           state);
}