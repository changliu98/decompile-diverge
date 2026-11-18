extern stbtt_int32 stbtt__GetGlyphGPOSInfoAdvance(const stbtt_fontinfo *info, stbtt_int32 glyph1, stbtt_int32 glyph2)
{
   stbtt_uint16 lookupListOffset;
   stbtt_uint8 *lookupList;
   stbtt_uint16 lookupCount;
   stbtt_uint16 i;
   stbtt_uint16 subtableOffset;
   stbtt_uint8 *subTableOffsets;
   stbtt_uint16 subTableCount;
   stbtt_uint16 posFormat;
   stbtt_uint16 coverageOffset;
   stbtt_uint8 *coverageIndexToGlyphIndex;
   stbtt_uint16 coverageIndex;
   stbtt_uint16 pairValueCount;
   stbtt_uint16 pairValueOffset;
   stbtt_uint8 *pairValueTable;
   stbtt_uint16 pairValuePairSetCount;
   stbtt_uint16 pairValuePairSetOffset;
   stbtt_uint8 *pairValuePairSetTable;
   stbtt_uint16 pairValuePairSetPosTable;
   stbtt_uint16 pairValuePairSetPosFormat;
   stbtt_uint16 pairValuePairSetPosRuleCount;
   stbtt_uint16 pairValuePairSetPosRuleOffset;
   stbtt_uint8 *pairValuePairSetPosRuleTable;
   stbtt_uint16 pairValuePairSetPosRule1;
   stbtt_uint16 pairValuePairSetPosRule2;
   stbtt_uint16 pairValuePairSetPosRuleValue;
   stbtt_uint16 classDef1Offset;
   stbtt_uint16 classDef2Offset;
   stbtt_uint16 class1Count;
   stbtt_uint16 class2Count;
   stbtt_uint8 *class1Table;
   stbtt_uint8 *class2Table;
   stbtt_uint16 class1;
   stbtt_uint16 class2;
   stbtt_uint16 valueFormat1;
   stbtt_uint16 valueFormat2;
   stbtt_uint16 valueRecordPairSizeInBytes;
   stbtt_uint16 valueRecord1;
   stbtt_uint16 valueRecord2;
   stbtt_uint16 valueArrayOffset;
   stbtt_uint16 valueArraySize;
   stbtt_uint16 lookupType;
   stbtt_uint16 lookupOffset;
   stbtt_uint8 *lookupTable;
   stbtt_uint16 sti;
   stbtt_uint16 j;
   stbtt_uint16 k;
   stbtt_uint16 l;
   stbtt_uint16 m;
   stbtt_uint16 n;
   stbtt_uint16 r;
   stbtt_uint16 secondGlyph;
   stbtt_uint8 *data;

   if (!info->gpos)
      return 0;

   data = info->data + info->gpos;


   if (ttUSHORT(data) != 1)
      return 0;


   if (ttUSHORT(data + 2) != 0)
      return 0;


   lookupListOffset = ttUSHORT(data + 8);
   lookupList = data + lookupListOffset;
   lookupCount = ttUSHORT(lookupList);


   for (i=0; i < lookupCount; ++i) {
      lookupOffset = ttUSHORT(lookupList + 2 + 2 * i);
      lookupTable = data + lookupOffset;
      lookupType = ttUSHORT(lookupTable);
      subtableOffset = ttUSHORT(lookupTable + 4);
      subTableOffsets = lookupTable + subtableOffset;
      subTableCount = ttUSHORT(lookupTable + 6);

      if (lookupType != 2)
         continue;


      for (j=0; j < subTableCount; ++j) {
         subtableOffset = ttUSHORT(subTableOffsets + 2 + 2 * j);
         subTableOffsets = lookupTable + subtableOffset;
         posFormat = ttUSHORT(subTableOffsets);
         coverageOffset = ttUSHORT(subTableOffsets + 2);
         coverageIndexToGlyphIndex = subTableOffsets + coverageOffset;
         coverageIndex = stbtt__GetCoverageIndex(coverageIndexToGlyphIndex, glyph1);
         if (coverageIndex == -1)
            continue;

         switch (posFormat) {
         case 1:
            valueFormat1 = ttUSHORT(subTableOffsets + 4);
            valueFormat2 = ttUSHORT(subTableOffsets + 6);
            if (valueFormat1 != 4)
               return 0;
            if (valueFormat2 != 0)
               return 0;

            valueArrayOffset = ttUSHORT(subTableOffsets + 8);
            valueArraySize = ttUSHORT(subTableOffsets + valueArrayOffset);
            valueArrayOffset = ttUSHORT(subTableOffsets + valueArrayOffset + 2 + 2 * coverageIndex);
            valueArrayOffset += subtableOffset;
            secondGlyph = ttUSHORT(data + valueArrayOffset);


            if (coverageIndex >= valueArraySize)
               return 0;


            l=0; r=valueArraySize-1;
            while (l <= r) {
               m = (l+r) >> 1;
               secondGlyph = ttUSHORT(data + valueArrayOffset + 2 + 2 * m);
               if (glyph2 < secondGlyph)
                  r = m - 1;
               else if (glyph2 > secondGlyph)
                  l = m + 1;
               else
                  return ttSHORT(data + valueArrayOffset + 2 + 2 * m + 2);
            }
            break;

         case 2:
            valueFormat1 = ttUSHORT(subTableOffsets + 4);
            valueFormat2 = ttUSHORT(subTableOffsets + 6);
            if (valueFormat1 != 4)
               return 0;
            if (valueFormat2 != 0)
               return 0;

            classDef1Offset = ttUSHORT(subTableOffsets + 8);
            classDef2Offset = ttUSHORT(subTableOffsets + 10);
            class1Table = subTableOffsets + classDef1Offset;
            class2Table = subTableOffsets + classDef2Offset;
            class1Count = ttUSHORT(class1Table);
            class2Count = ttUSHORT(class2Table);
            class1 = stbtt__GetGlyphClass(class1Table + 2, glyph1);
            class2 = stbtt__GetGlyphClass(class2Table + 2, glyph2);
            valueArrayOffset = ttUSHORT(subTableOffsets + 12);
            valueArraySize = ttUSHORT(subTableOffsets + 14);


            if (class1 >= class1Count)
               return 0;
            if (class2 >= class2Count)
               return 0;


            return ttSHORT(subTableOffsets + 16 + 2 * class2 + valueArraySize * class1);

            break;

         default:
            return 0;
         }
      }
   }

   return 0;
}