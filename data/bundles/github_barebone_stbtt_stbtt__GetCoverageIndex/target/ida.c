stbtt_int32 __cdecl stbtt__GetCoverageIndex(stbtt_uint8 *coverageTable, int glyph)
{
  int v3; // [rsp+0h] [rbp-70h]
  stbtt_uint8 *rangeRecord; // [rsp+8h] [rbp-68h]
  int strawEnd; // [rsp+14h] [rbp-5Ch]
  int strawStart; // [rsp+18h] [rbp-58h]
  int m_0; // [rsp+1Ch] [rbp-54h]
  stbtt_int32 r_0; // [rsp+20h] [rbp-50h]
  stbtt_int32 l_0; // [rsp+24h] [rbp-4Ch]
  int straw; // [rsp+48h] [rbp-28h]
  int m; // [rsp+4Ch] [rbp-24h]
  stbtt_int32 r; // [rsp+50h] [rbp-20h]
  stbtt_int32 l; // [rsp+54h] [rbp-1Ch]

  v3 = ttUSHORT(coverageTable);
  if ( v3 == 1 )
  {
    l = 0;
    r = ttUSHORT(coverageTable + 2) - 1;
    while ( l <= r )
    {
      m = (r + l) >> 1;
      straw = ttUSHORT(&coverageTable[2 * m + 4]);
      if ( glyph >= straw )
      {
        if ( glyph <= straw )
          return (r + l) >> 1;
        l = m + 1;
      }
      else
      {
        r = m - 1;
      }
    }
    return -1;
  }
  if ( v3 == 2 )
  {
    l_0 = 0;
    r_0 = ttUSHORT(coverageTable + 2) - 1;
    while ( l_0 <= r_0 )
    {
      m_0 = (r_0 + l_0) >> 1;
      rangeRecord = &coverageTable[6 * m_0 + 4];
      strawStart = ttUSHORT(rangeRecord);
      strawEnd = ttUSHORT(rangeRecord + 2);
      if ( glyph >= strawStart )
      {
        if ( glyph <= strawEnd )
          return glyph + ttUSHORT(rangeRecord + 4) - strawStart;
        l_0 = m_0 + 1;
      }
      else
      {
        r_0 = m_0 - 1;
      }
    }
    return -1;
  }
  return -1;
}