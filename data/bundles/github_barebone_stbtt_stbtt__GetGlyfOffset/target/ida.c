int __cdecl stbtt__GetGlyfOffset(const stbtt_fontinfo *info, int glyph_index)
{
  int glyf; // [rsp+4h] [rbp-2Ch]
  int v5; // [rsp+8h] [rbp-28h]
  int v6; // [rsp+Ch] [rbp-24h]
  int v7; // [rsp+10h] [rbp-20h]
  int g2; // [rsp+14h] [rbp-1Ch]
  int g1; // [rsp+18h] [rbp-18h]

  if ( info->cff.size )
    _assert_fail("!info->cff.size", "func.c", 0x647u, "int stbtt__GetGlyfOffset(const stbtt_fontinfo *, int)");
  if ( glyph_index >= info->numGlyphs )
    return -1;
  if ( info->indexToLocFormat >= 2 )
    return -1;
  if ( info->indexToLocFormat )
  {
    glyf = info->glyf;
    g1 = ttULONG(&info->data[4 * glyph_index + info->loca]) + glyf;
    v5 = info->glyf;
    g2 = ttULONG(&info->data[4 * glyph_index + 4 + info->loca]) + v5;
  }
  else
  {
    v6 = info->glyf;
    g1 = 2 * ttUSHORT(&info->data[2 * glyph_index + info->loca]) + v6;
    v7 = info->glyf;
    g2 = 2 * ttUSHORT(&info->data[2 * glyph_index + 2 + info->loca]) + v7;
  }
  if ( g1 == g2 )
    return -1;
  else
    return g1;
}