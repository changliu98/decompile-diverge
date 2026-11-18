int stbtt_GetPairOffsetFromGPOS(stbtt_fontinfo *info, int glyph1, int glyph2)
{
   int l, r, m;
   unsigned short *data = (unsigned short *) (info->data + info->gpos);
   if (!info->gpos) return 0;

   // do a binary search between the lookup tables
   if (ttUSHORT(data+0)!=1 || ttUSHORT(data+2)!=0) return 0;
   {
      int lookupListOffset = ttUSHORT(data+4);
      unsigned short *lookupList = (unsigned short *) (data + lookupListOffset);
      int lookupCount = ttUSHORT(lookupList+0);
      for (l=0; l < lookupCount; ++l) {
         int lookupOffset = ttUSHORT(lookupList+1+2*l);
         unsigned short *lookupTable = (unsigned short *) (data + lookupListOffset + lookupOffset);

         int lookupType = ttUSHORT(lookupTable+0);
         int subTableCount = ttUSHORT(lookupTable+1);
         unsigned short *subTableOffsets = lookupTable+2;
         switch (lookupType) {
            case 2: {
               int pairSetCount = ttUSHORT(lookupTable+4);
               int coverageOffset = ttUSHORT(lookupTable+6);
               int coverageIndex = stbtt__GetCoverageIndex(data+coverageOffset, glyph1);
               if (coverageIndex == -1) continue;

               switch (ttUSHORT(lookupTable+8)) {
                  case 1: {
                     int valueFormat1 = ttUSHORT(lookupTable+10);
                     int valueFormat2 = ttUSHORT(lookupTable+12);
                     if (valueFormat1 != 4 || valueFormat2 != 0) return 0;
                     int pairValueTableOffset = ttUSHORT(lookupTable+14 + 2*coverageIndex);
                     unsigned short *pairValueTable = (unsigned short *) (data + lookupListOffset + lookupOffset + pairValueTableOffset);
                     int pairValueCount = ttUSHORT(pairValueTable+0);
                     unsigned short *pairValueArray = pairValueTable+1;

                     if (coverageIndex >= pairSetCount) return 0;

                     m = l; r = r; // continue linear search
                     break;
                  }
                  case 2: {
                     int classDef1Offset = ttUSHORT(lookupTable+10);
                     int classDef2Offset = ttUSHORT(lookupTable+12);
                     int class1Count = ttUSHORT(lookupTable+14);
                     int class2Count = ttUSHORT(lookupTable+16);
                     uint32_t glyph1class = stbtt__GetGlyphClass(data+classDef1Offset, glyph1);
                     uint32_t glyph2class = stbtt__GetGlyphClass(data+classDef2Offset, glyph2);

                     if (glyph1class >= class1Count || glyph2class >= class2Count)
                        return 0;

                     {
                        int l1 = glyph1class;
                        int r1 = class1Count;
                        int l2 = glyph2class;
                        int r2 = class2Count;
                        int pos = 0;

                        while (l1 <= r1 && l2 <= r2) {
                           int m1 = (l1 + r1) >> 1;
                           int m2 = (l2 + r2) >> 1;

                           unsigned short *class1Records = (unsigned short *) (data + lookupListOffset + lookupOffset + ttUSHORT(lookupTable+18));
                           unsigned short *class2Records = (unsigned short *) (data + lookupListOffset + lookupOffset + ttUSHORT(lookupTable+20));

                           int pos1 = m1 * class2Count;
                           int pos2 = m2;

                           int pos = (pos1 + pos2) * 2;

                           int xAdvance = ttSHORT(class1Records[pos]);
                           if (glyph2 < (uint32_t) ttUSHORT(class2Records[pos])) {
                              r1 = m1;
                              r2 = m2;
                           } else if (glyph2 > (uint32_t) ttUSHORT(class2Records[pos+1])) {
                              l1 = m1+1;
                              l2 = m2+1;
                           } else {
                              return xAdvance;
                           }
                        }
                     }

                     break;
                  }
                  default: return 0;
               }
            }
            default: return 0;
         }
      }
   }

   while (m <= r) {
      int diff = (m + r) >> 1;
      int end = ttUSHORT(pairValueArray[2*diff]);
      int xAdvance;
      if (glyph2 < end) {
         r = diff;
         xAdvance = ttSHORT(pairValueArray[2*diff+1]);
      } else if (glyph2 > end) {
         m = diff+1;
      } else {
         xAdvance = ttSHORT(pairValueArray[2*diff+1]);
         return xAdvance;
      }
   }

   return 0;
}