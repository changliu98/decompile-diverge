int stbtt__GetGlyfOffset(const stbtt_fontinfo *info, int glyph_index) {
  int start, end;
  (void)((!info->cff.size) ||
         (_stb_assert(
              "!info->cff.size", "func.c", 1607,
              "int stbtt__GetGlyfOffset(const stbtt_fontinfo *, int)"),
          0));
  if (glyph_index >= info->numGlyphs) return -1;
  if (info->indexToLocFormat >= 2) return -1;
  if (info->indexToLocFormat == 0) {
    start = info->glyf + ttUSHORT(info->indexToLocFormat_data + glyph_index * 2) *
                             2;
    end = info->glyf + ttUSHORT(info->indexToLocFormat_data + glyph_index * 2 +
                                2) *
                           2;
  } else {
    start = info->glyf + ttULONG(info->indexToLocFormat_data + glyph_index * 4);
    end = info->glyf + ttULONG(info->indexToLocFormat_data + glyph_index * 4 +
                               4);
  }
  return start == end ? -1 : start;
}