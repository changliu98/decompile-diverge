stbtt_int32 stbtt__GetCoverageIndex(stbtt_uint8 *coverageTable, int glyph)
{
   stbtt_uint16 coverageFormat = ttUSHORT(coverageTable);
   switch (coverageFormat) {
      case 1: {
         stbtt_uint16 glyphCount = ttUSHORT(coverageTable+2);
         stbtt_uint16 *glyphArray = (stbtt_uint16 *) (coverageTable+4);
         stbtt_uint16 l,r,m;

         l = 0;
         r = glyphCount - 1;
         while (l <= r) {
            m = (l + r) >> 1;
            if (glyph < glyphArray[m])
               r = m - 1;
            else if (glyph > glyphArray[m])
               l = m + 1;
            else
               return m;
         }
         break;
      }

      case 2: {
         stbtt_uint16 rangeCount = ttUSHORT(coverageTable+2);
         stbtt_uint16 *rangeArray = (stbtt_uint16 *) (coverageTable+4);
         stbtt_uint16 l,r,m;

         l = 0;
         r = rangeCount - 1;
         while (l <= r) {
            m = (l + r) >> 1;
            if (glyph < rangeArray[m*3])
               r = m - 1;
            else if (glyph > rangeArray[m*3+1])
               l = m + 1;
            else
               return rangeArray[m*3+2] + glyph - rangeArray[m*3];
         }
         break;
      }

      default:
         break;
   }
   return -1;
}