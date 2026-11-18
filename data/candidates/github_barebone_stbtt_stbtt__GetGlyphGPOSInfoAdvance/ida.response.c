stbtt_int32 __cdecl stbtt__GetGlyphGPOSInfoAdvance(const stbtt_fontinfo *info, int glyph1, int glyph2)
{
  stbtt_uint16 class2Count; // [rsp+18h] [rbp-D8h]
  stbtt_uint16 class1Count; // [rsp+1Ah] [rbp-D6h]
  int glyph2class; // [rsp+1Ch] [rbp-D4h]
  int glyph1class; // [rsp+20h] [rbp-D0h]
  stbtt_uint16 classDef2Offset; // [rsp+26h] [rbp-CAh]
  stbtt_uint16 classDef1Offset; // [rsp+28h] [rbp-C8h]
  stbtt_uint16 valueFormat2_0; // [rsp+2Ah] [rbp-C6h]
  stbtt_uint16 valueFormat1_0; // [rsp+2Ch] [rbp-C4h]
  stbtt_uint8 *pairValueArray; // [rsp+40h] [rbp-B0h]
  stbtt_uint16 pairValueCount; // [rsp+4Eh] [rbp-A2h]
  stbtt_uint8 *pairValueTable; // [rsp+50h] [rbp-A0h]
  stbtt_uint16 pairSetCount; // [rsp+5Ah] [rbp-96h]
  stbtt_uint16 valueFormat2; // [rsp+60h] [rbp-90h]
  stbtt_uint16 valueFormat1; // [rsp+62h] [rbp-8Eh]
  int straw; // [rsp+68h] [rbp-88h]
  int m; // [rsp+6Ch] [rbp-84h]
  stbtt_int32 r; // [rsp+70h] [rbp-80h]
  stbtt_int32 l; // [rsp+74h] [rbp-7Ch]
  int coverageIndex; // [rsp+78h] [rbp-78h]
  stbtt_uint16 coverageOffset; // [rsp+7Ch] [rbp-74h]
  stbtt_uint16 posFormat; // [rsp+7Eh] [rbp-72h]
  stbtt_uint8 *table; // [rsp+80h] [rbp-70h]
  stbtt_uint16 subTableCount; // [rsp+9Ch] [rbp-54h]
  stbtt_uint16 lookupType; // [rsp+9Eh] [rbp-52h]
  stbtt_uint8 *lookupTable; // [rsp+A0h] [rbp-50h]
  stbtt_int32 sti; // [rsp+B0h] [rbp-40h]
  stbtt_int32 i; // [rsp+B4h] [rbp-3Ch]
  stbtt_uint8 *data; // [rsp+B8h] [rbp-38h]
  stbtt_uint16 lookupCount; // [rsp+C6h] [rbp-2Ah]
  stbtt_uint8 *lookupList; // [rsp+C8h] [rbp-28h]

  if ( !info->gpos )
    return 0;
  data = &info->data[info->gpos];
  if ( ttUSHORT(data) != 1 )
    return 0;
  if ( ttUSHORT(data + 2) )
    return 0;
  lookupList = &data[ttUSHORT(data + 8)];
  lookupCount = ttUSHORT(lookupList);
  for ( i = 0; i < lookupCount; ++i )
  {
    lookupTable = &lookupList[ttUSHORT(&lookupList[2 * i + 2])];
    lookupType = ttUSHORT(lookupTable);
    subTableCount = ttUSHORT(lookupTable + 4);
    if ( lookupType == 2 )
    {
      for ( sti = 0; sti < subTableCount; ++sti )
      {
        table = &lookupTable[ttUSHORT(&lookupTable[2 * sti + 6])];
        posFormat = ttUSHORT(table);
        coverageOffset = ttUSHORT(table + 2);
        coverageIndex = stbtt__GetCoverageIndex(&table[coverageOffset], glyph1);
        if ( coverageIndex != -1 )
        {
          if ( posFormat != 1 )
          {
            if ( posFormat != 2 )
              return 0;
            valueFormat1_0 = ttUSHORT(table + 4);
            valueFormat2_0 = ttUSHORT(table + 6);
            if ( valueFormat1_0 != 4 || valueFormat2_0 )
              return 0;
            classDef1Offset = ttUSHORT(table + 8);
            classDef2Offset = ttUSHORT(table + 10);
            glyph1class = stbtt__GetGlyphClass(&table[classDef1Offset], glyph1);
            glyph2class = stbtt__GetGlyphClass(&table[classDef2Offset], glyph2);
            class1Count = ttUSHORT(table + 12);
            class2Count = ttUSHORT(table + 14);
            if ( glyph1class < 0 || glyph1class >= class1Count )
              return 0;
            if ( glyph2class >= 0 && glyph2class < class2Count )
              return ttSHORT(&table[2 * class2Count * glyph1class + 16 + 2 * glyph2class]);
            return 0;
          }
          valueFormat1 = ttUSHORT(table + 4);
          valueFormat2 = ttUSHORT(table + 6);
          if ( valueFormat1 != 4 || valueFormat2 )
            return 0;
          pairSetCount = ttUSHORT(table + 8);
          pairValueTable = &table[ttUSHORT(&table[2 * coverageIndex + 10])];
          pairValueCount = ttUSHORT(pairValueTable);
          pairValueArray = pairValueTable + 2;
          if ( coverageIndex >= pairSetCount )
            return 0;
          r = pairValueCount - 1;
          l = 0;
          while ( l <= r )
          {
            m = (r + l) >> 1;
            straw = ttUSHORT(&pairValueArray[4 * m]);
            if ( glyph2 >= straw )
            {
              if ( glyph2 <= straw )
                return ttSHORT(&pairValueArray[4 * m + 2]);
              l = m + 1;
            }
            else
            {
              r = m - 1;
            }
          }
        }
      }
    }
  }
  return 0;
}