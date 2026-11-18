int stbtt__GetGlyphClass(void *classDefTable, int glyph)
{
   int class = stbtt_GetFontClass(classDefTable);
   if (class == 1)
   {
      unsigned char *cd = (unsigned char *)classDefTable;
      int startGlyphID = (int)(unsigned int)stbtt_GetFontClassDef1(cd);
      int glyphCount = (int)(unsigned int)stbtt_GetFontClassDef1(cd + 2);
      if (glyph >= startGlyphID && glyph < startGlyphID + glyphCount)
         return (int)(unsigned int)stbtt_GetFontClassDef1(cd + 6 + (glyph - startGlyphID) * 2);
      return 0;
   }
   if (class == 2)
   {
      int i;
      int l = 0; int r = (int)(unsigned int)stbtt_GetFontClassDef1(classDefTable + 2) - 1;
      while (l <= r)
      {
         int m = (l + r) >> 1;
         unsigned char *cd = (unsigned char *)classDefTable + 4 + m * 6;
         int strawStart = (int)(unsigned int)stbtt_GetFontClassDef1(cd);
         int strawEnd = (int)(unsigned int)stbtt_GetFontClassDef1(cd + 2);
         if (glyph < strawStart)
            r = m - 1;
         else if (glyph > strawEnd)
            l = m + 1;
         else
            return (int)(unsigned int)stbtt_GetFontClassDef1(cd + 4);
      }
      return 0;
   }
   return -1;
}