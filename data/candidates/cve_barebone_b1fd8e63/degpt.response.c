void gitn_box_del(GF_Box *s)

{
  GroupIdToNameBox *ptr;
  u32 i;
  GF_Box *s_local;
  
  if (s != (GF_Box *)0x0) {
    for (i = 0; i < (ushort)s[1].type; i = i + 1) {
      if (*(long *)(s[1].size + (ulong)i * 0x10 + 8) != 0) {
        gf_free(*(void **)(s[1].size + (ulong)i * 0x10 + 8));
      }
    }
    if (s[1].size != 0) {
      gf_free((void *)s[1].size);
    }
    gf_free(s);
  }
  return;
}