static int init_font(ttf_t *ttf) {
  unsigned version;
  unsigned head;
  unsigned hhea;
  if (!is_safe_offset(ttf, 0, 12)) return -1;
  version = getu32(ttf, 0);
  if (version != 0x00010000 && version != 0x7472616b) return -1;
  if (gettable(ttf, "head", &head) < 0) return -1;
  if (!is_safe_offset(ttf, head, 54)) return -1;
  ttf->units_per_em = getu16(ttf, head + 18);
  ttf->x_min = geti16(ttf, head + 50);
  if (gettable(ttf, "hhea", &hhea) < 0) return -1;
  if (!is_safe_offset(ttf, hhea, 36)) return -1;
  ttf->x_max = getu16(ttf, hhea + 34);
  return 0;
}