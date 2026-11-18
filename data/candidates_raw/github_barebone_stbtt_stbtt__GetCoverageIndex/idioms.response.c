int stbtt_GetGlyphIndexFromCmap(unsigned char *cmap, int glyph)
{
   int type = stbtt_GetCmapType(cmap);
   if (type == 1)
   {
      int l = 0; int r = stbtt_GetCmapSubtableCount(cmap) - 1;
      while (l <= r)
      {
         int m = (l + r) >> 1;
         int straw = stbtt_GetCmapId(cmap + 4 + m * 2);
         if (glyph < straw)
            r = m - 1;
         else if (glyph > straw)
            l = m + 1;
         else
            return m;
      }
      return -1;
   }
   else if (type == 2)
   {
      int l = 0; int r = stbtt_GetCmapSubtableCount(cmap) - 1;
      while (l <= r)
      {
         int m = (l + r) >> 1;
         unsigned char *sub = cmap + 4 + m * 6;
         int strawStart = stbtt_GetCmapId(sub);
         int strawEnd = stbtt_GetCmapId(sub + 2);
         if (glyph < strawStart)
            r = m - 1;
         else if (glyph > strawEnd)
            l = m + 1;
         else
            return glyph + stbtt_GetCmapId(sub + 4) - strawStart;
      }
      return -1;
   }
   return -1;
}