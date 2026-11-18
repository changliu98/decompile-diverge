stbtt_int32 stbtt__GetGlyphClass(stbtt_uint8 *classDefTable,int glyph)

{
  stbtt_uint16 sVar1;
  stbtt_uint16 sVar2;
  int iVar3;
  stbtt_uint8 *p;
  stbtt_uint8 *classRangeRecord;
  int needle;
  int strawEnd;
  int strawStart;
  stbtt_int32 m;
  stbtt_int32 r;
  stbtt_int32 l;
  stbtt_uint8 *classRangeRecords;
  stbtt_uint16 classRangeCount;
  stbtt_uint8 *classDef1ValueArray;
  stbtt_uint16 glyphCount;
  stbtt_uint16 startGlyphID;
  stbtt_uint16 classDefFormat;
  int glyph_local;
  stbtt_uint8 *classDefTable_local;
  
  sVar1 = ttUSHORT(classDefTable);
  if (sVar1 == 1) {
    sVar1 = ttUSHORT(classDefTable + 2);
    sVar2 = ttUSHORT(classDefTable + 4);
    if (((int)(uint)sVar1 <= glyph) && (glyph < (int)((uint)sVar1 + (uint)sVar2))) {
      sVar1 = ttUSHORT(classDefTable + (long)(int)((glyph - (uint)sVar1) * 2) + 6);
      return (uint)sVar1;
    }
  }
  else {
    if (sVar1 != 2) {
      return -1;
    }
    sVar1 = ttUSHORT(classDefTable + 2);
    l = 0;
    r = sVar1 - 1;
    while (l <= r) {
      iVar3 = l + r >> 1;
      p = classDefTable + (long)(iVar3 * 6) + 4;
      sVar1 = ttUSHORT(p);
      sVar2 = ttUSHORT(p + 2);
      if (glyph < (int)(uint)sVar1) {
        r = iVar3 + -1;
      }
      else {
        if (glyph <= (int)(uint)sVar2) {
          sVar1 = ttUSHORT(p + 4);
          return (uint)sVar1;
        }
        l = iVar3 + 1;
      }
    }
  }
  return 0;
}