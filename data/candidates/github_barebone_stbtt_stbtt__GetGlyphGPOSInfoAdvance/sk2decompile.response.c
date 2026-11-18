static stbtt_int16 stbtt_GetGlyphGPOSInfoAdvance(const stbtt_fontinfo *info,
                                                 int glyph, int next_glyph) {
  if (!info->gpos_table_start) return 0;
  unsigned char *table = info->data + info->gpos_table_start;
  if (ttUSHORT(table) != 1) return 0;
  if (ttUSHORT(table + 2) != 0) return 0;
  unsigned char *p = table + ttUSHORT(table + 8);
  stbtt_uint16 num_pairs = ttUSHORT(p);
  stbtt_uint16 i;
  for (i = 0; i < num_pairs; ++i) {
    unsigned char *pair = p + ttUSHORT(p + 2 + 2 * i);
    stbtt_uint16 type = ttUSHORT(pair);
    stbtt_uint16 num_subtables = ttUSHORT(pair + 4);
    if (type == 2) {
      stbtt_uint16 j;
      for (j = 0; j < num_subtables; ++j) {
        unsigned char *subtable = pair + ttUSHORT(pair + 6 + 2 * j);
        stbtt_uint16 subtype = ttUSHORT(subtable);
        stbtt_uint16 sublen = ttUSHORT(subtable + 4);
        int index = stbtt__GetCoverageIndex(subtable + sublen, glyph);
        if (index != -1) {
          if (subtype == 1) {
            stbtt_uint16 coverage = ttUSHORT(subtable + 4);
            stbtt_uint16 class_set = ttUSHORT(subtable + 6);
            if (coverage != 4 || class_set != 0) return 0;
            stbtt_uint16 class_count = ttUSHORT(subtable + 8);
            unsigned char *class_data =
                subtable + ttUSHORT(subtable + 10 + index * 2);
            stbtt_uint16 class_id = ttUSHORT(class_data);
            unsigned char *class_offset = class_data + 2;
            if (index >= class_count) return 0;
            int top = class_id - 1;
            int bottom = 0;
            while (bottom <= top) {
              int mid = (top + bottom) >> 1;
              int mid_glyph = ttUSHORT(class_offset + 4 * mid);
              if (next_glyph < mid_glyph)
                top = mid - 1;
              else if (next_glyph > mid_glyph)
                bottom = mid + 1;
              else
                return ttSHORT(class_offset + 4 * mid + 2);
            }
          } else if (subtype == 2) {
            stbtt_uint16 coverage2 = ttUSHORT(subtable + 4);
            stbtt_uint16 coverage3 = ttUSHORT(subtable + 6);
            if (coverage2 != 4 || coverage3 != 0) return 0;
            stbtt_uint16 class_set2 = ttUSHORT(subtable + 8);
            stbtt_uint16 class_set3 = ttUSHORT(subtable + 10);
            int glyph_class = stbtt__GetGlyphClass(subtable + class_set2, glyph);
            int next_glyph_class =
                stbtt__GetGlyphClass(subtable + class_set3, next_glyph);
            stbtt_uint16 class_count2 = ttUSHORT(subtable + 12);
            stbtt_uint16 class_count3 = ttUSHORT(subtable + 14);
            if (glyph_class < 0 || glyph_class >= class_count2) return 0;
            if (next_glyph_class < 0 || next_glyph_class >= class_count3)
              return 0;
            return ttSHORT(subtable + 16 + 2 * glyph_class +
                           2 * class_count3 * glyph_class + 2 * next_glyph_class);
          } else
            return 0;
        }
      }
    }
  }
  return 0;
}