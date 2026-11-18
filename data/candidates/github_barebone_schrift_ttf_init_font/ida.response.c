int __cdecl init_font(SFT_Font *font)
{
  uint_least16_t v1; // ax
  int_least16_t v2; // ax
  uint_least16_t v3; // ax
  uint_fast32_t hhea; // [rsp+8h] [rbp-28h] BYREF
  uint_fast32_t head; // [rsp+10h] [rbp-20h] BYREF
  uint_fast32_t scalerType; // [rsp+18h] [rbp-18h]
  SFT_Font *fonta; // [rsp+20h] [rbp-10h]

  fonta = font;
  if ( !is_safe_offset(font, 0LL, 0xCuLL) )
    return -1;
  scalerType = getu32(fonta, 0LL);
  if ( scalerType != 0x10000 && scalerType != 1953658213 )
    return -1;
  if ( gettable(fonta, "head", &head) < 0 )
    return -1;
  if ( !is_safe_offset(fonta, head, 0x36uLL) )
    return -1;
  v1 = getu16(fonta, head + 18);
  fonta->unitsPerEm = v1;
  v2 = geti16(fonta, head + 50);
  fonta->locaFormat = v2;
  if ( gettable(fonta, "hhea", &hhea) < 0 )
    return -1;
  if ( !is_safe_offset(fonta, hhea, 0x24uLL) )
    return -1;
  v3 = getu16(fonta, hhea + 34);
  fonta->numLongHmtx = v3;
  return 0;
}