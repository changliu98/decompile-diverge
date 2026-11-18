stbtt_int32 __cdecl stbtt__GetGlyphClass(stbtt_uint8 *classDefTable, int glyph)
{
  int v3; // [rsp+4h] [rbp-5Ch]
  stbtt_uint8 *classRangeRecord; // [rsp+8h] [rbp-58h]
  int strawEnd; // [rsp+14h] [rbp-4Ch]
  int strawStart; // [rsp+18h] [rbp-48h]
  int m; // [rsp+1Ch] [rbp-44h]
  stbtt_int32 r; // [rsp+20h] [rbp-40h]
  stbtt_int32 l; // [rsp+24h] [rbp-3Ch]
  stbtt_uint16 glyphCount; // [rsp+46h] [rbp-1Ah]
  stbtt_uint16 startGlyphID; // [rsp+48h] [rbp-18h]

  v3 = ttUSHORT(classDefTable);
  if ( v3 == 1 )
  {
    startGlyphID = ttUSHORT(classDefTable + 2);
    glyphCount = ttUSHORT(classDefTable + 4);
    if ( glyph >= startGlyphID && glyph < glyphCount + startGlyphID )
      return ttUSHORT(&classDefTable[2 * (glyph - startGlyphID) + 6]);
    return 0;
  }
  if ( v3 == 2 )
  {
    l = 0;
    r = ttUSHORT(classDefTable + 2) - 1;
    while ( l <= r )
    {
      m = (r + l) >> 1;
      classRangeRecord = &classDefTable[6 * m + 4];
      strawStart = ttUSHORT(classRangeRecord);
      strawEnd = ttUSHORT(classRangeRecord + 2);
      if ( glyph >= strawStart )
      {
        if ( glyph <= strawEnd )
          return ttUSHORT(classRangeRecord + 4);
        l = m + 1;
      }
      else
      {
        r = m - 1;
      }
    }
    return 0;
  }
  return -1;
}