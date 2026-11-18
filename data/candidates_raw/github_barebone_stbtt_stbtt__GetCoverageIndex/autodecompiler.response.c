static int stbtt__searchGlyphRange(unsigned char *coverage, stbtt_uint16 glyph)
{
   stbtt_uint16 coverageFormat = ttUSHORT(coverage);
   int result;
   switch (coverageFormat) {
      case 1: {
         stbtt_uint16 glyphCount = ttUSHORT(coverage+2);
         int l=0, r=(int)glyphCount-1, m;
         stbtt_uint16 *array = (stbtt_uint16 *) (coverage+4);
         while (l <= r) {
            m = (l + r) >> 1;
            if (glyph < array[m])
               r = m - 1;
            else if (glyph > array[m])
               l = m + 1;
            else {
               result = m;
               goto done;
            }
         }
         break;
      }

      case 2: {
         stbtt_uint16 rangeCount = ttUSHORT(coverage+2);
         stbtt_uint16 *rangeArray = (stbtt_uint16 *) (coverage+4);
         int l=0, r=(int)rangeCount-1, m;
         stbtt_uint16 *rangeRecords = rangeArray;
         while (l <= r) {
            m = (l + r) >> 1;
            {
               stbtt_uint16 start = ttUSHORT(rangeRecords + m*3 + 0);
               stbtt_uint16 end = ttUSHORT(rangeRecords + m*3 + 2);
               if (glyph < start)
                  r = m - 1;
               else if (glyph > end)
                  l = m + 1;
               else {
                  stbtt_uint16 index = ttUSHORT(rangeRecords + m*3 + 4);
                  result = index + glyph - start;
                  goto done;
               }
            }
         }
         break;
      }

      default: return -1;
   }

   result = -1;
done:
   return result;
}