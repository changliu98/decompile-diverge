int stbtt__GetGlyphClass(stbtt_uint8 *classDefTable, int glyph)
{
   int left, right;
   stbtt_uint16 classDefFormat;
   stbtt_uint16 glyphCount;
   stbtt_uint8 *classDef1ValueArray;
   stbtt_uint16 startGlyphID;
   stbtt_uint16 classRangeCount;
   stbtt_uint8 *classRangeRecords;

   classDefFormat = ttUSHORT(classDefTable);
   if (classDefFormat == 1) {
      stbtt_uint16 start, end;
      classDef1ValueArray = classDefTable + 4;
      start = ttUSHORT(classDefTable+2);
      end = start + ttUSHORT(classDefTable+4);
      if (glyph >= start && glyph < end)
         return classDef1ValueArray[glyph - start];
   } else if (classDefFormat == 2) {
      classRangeRecords = classDefTable + 4;
      classRangeCount = ttUSHORT(classDefTable+2);
      left = 0; right = classRangeCount-1;
      while (left <= right) {
         stbtt_uint16 start, end, value;
         stbtt_uint8 *classRange;
         int mid = (left + right) >> 1;
         classRange = classRangeRecords + mid * 6;
         start = ttUSHORT(classRange);
         end = ttUSHORT(classRange+2);
         value = ttUSHORT(classRange+4);
         if (glyph < start)
            right = mid - 1;
         else if (glyph > end)
            left = mid + 1;
         else
            return value;
      }
   }
   return 0;
}