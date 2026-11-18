stbtt_int32 stbtt__GetCoverageIndex(stbtt_uint8 *coverageTable,int glyph)

{
  stbtt_uint16 sVar1;
  stbtt_uint16 sVar2;
  int iVar3;
  stbtt_uint8 *p;
  stbtt_uint16 startCoverageIndex;
  stbtt_uint8 *rangeRecord;
  int needle_1;
  int strawEnd;
  int strawStart;
  stbtt_int32 m_1;
  stbtt_int32 r_1;
  stbtt_int32 l_1;
  stbtt_uint8 *rangeArray;
  stbtt_uint16 rangeCount;
  stbtt_uint16 glyphID;
  stbtt_uint8 *glyphArray;
  int needle;
  int straw;
  stbtt_int32 m;
  stbtt_int32 r;
  stbtt_int32 l;
  stbtt_uint16 glyphCount;
  stbtt_uint16 coverageFormat;
  int glyph_local;
  stbtt_uint8 *coverageTable_local;
  
  sVar1 = ttUSHORT(coverageTable);
  if (sVar1 == 1) {
    sVar1 = ttUSHORT(coverageTable + 2);
    l = 0;
    r = sVar1 - 1;
    while (l <= r) {
      iVar3 = l + r >> 1;
      sVar1 = ttUSHORT(coverageTable + (long)(iVar3 << 1) + 4);
      if (glyph < (int)(uint)sVar1) {
        r = iVar3 + -1;
      }
      else {
        if (glyph <= (int)(uint)sVar1) {
          return iVar3;
        }
        l = iVar3 + 1;
      }
    }
  }
  else {
    if (sVar1 != 2) {
      return -1;
    }
    sVar1 = ttUSHORT(coverageTable + 2);
    l_1 = 0;
    r_1 = sVar1 - 1;
    while (l_1 <= r_1) {
      iVar3 = l_1 + r_1 >> 1;
      p = coverageTable + (long)(iVar3 * 6) + 4;
      sVar1 = ttUSHORT(p);
      sVar2 = ttUSHORT(p + 2);
      if (glyph < (int)(uint)sVar1) {
        r_1 = iVar3 + -1;
      }
      else {
        if (glyph <= (int)(uint)sVar2) {
          sVar2 = ttUSHORT(p + 4);
          return ((uint)sVar2 + glyph) - (uint)sVar1;
        }
        l_1 = iVar3 + 1;
      }
    }
  }
  return -1;
}