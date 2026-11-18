int stbtt__GetGlyfOffset(const struct stbtt_fontinfo *info, int glyph_index)
{
  int offset1; int offset2;
  ((void) sizeof ((!info->cff.size) ? 1 : 0), __extension__ ({ if (!info->cff.size) ; else __assert_fail ("!info->cff.size", "func.c", 1607, __extension__ __PRETTY_FUNCTION__); }));
  if (glyph_index >= info->numGlyphs)
    return -1;
  if (info->indexToLocFormat >= 2)
    return -1;
  if (info->indexToLocFormat == 0) {
    int offset = info->glyf;
    offset += 2 * stbtt__GetShort(info->data + info->loca + 2 * glyph_index);
    offset1 = offset;
    offset = info->glyf;
    offset += 2 * stbtt__GetShort(info->data + info->loca + 2 * glyph_index + 2);
    offset2 = offset;
  } else {
    int offset = info->glyf;
    offset += stbtt__GetLong(info->data + info->loca + 4 * glyph_index);
    offset1 = offset;
    offset = info->glyf;
    offset += stbtt__GetLong(info->data + info->loca + 4 * glyph_index + 4);
    offset2 = offset;
  }
  if (offset1 == offset2)
    return -1;
  return offset1;
}