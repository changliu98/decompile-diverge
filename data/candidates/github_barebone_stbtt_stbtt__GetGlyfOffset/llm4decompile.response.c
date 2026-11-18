int stbtt__GetGlyfOffset(const stbtt_fontinfo *info, int glyph_index)
{
   int g1,g2;

   if (!((!info->cff.size))) { __assert_fail("!info->cff.size", "func.c", 1607, "int stbtt__GetGlyfOffset(const stbtt_fontinfo *, int)"); };

   if (glyph_index >= info->numGlyphs) return -1;
   if (info->indexToLocFormat >= 2) return -1;

   if (info->indexToLocFormat == 0) {
      g1 = info->glyf + ttUSHORT(info->data+info->loca+glyph_index*2) * 2;
      g2 = info->glyf + ttUSHORT(info->data+info->loca+glyph_index*2+2) * 2;
   } else {
      g1 = info->glyf + ttULONG (info->data+info->loca+glyph_index*4);
      g2 = info->glyf + ttULONG (info->data+info->loca+glyph_index*4+4);
   }

   return g1==g2 ? -1 : g1;
}