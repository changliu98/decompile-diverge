int __cdecl init_font(SFT_Font *font)
{
  uint_fast32_t head_offset;
  uint_fast32_t hhea_offset;
  uint_fast32_t scaler_type;

  // Validate the font header and check the scaler type
  if (!is_safe_offset(font, 0LL, 0xCuLL))
    return -1;
    
  scaler_type = getu32(font, 0LL);
  if (scaler_type != 0x10000 && scaler_type != 1953658213) // 0x10000 = TrueType, 1953658213 = 'OTTO' (CFF)
    return -1;

  // Read 'head' table
  if (gettable(font, "head", &head_offset) < 0)
    return -1;
  if (!is_safe_offset(font, head_offset, 0x36uLL))
    return -1;
    
  font->unitsPerEm = getu16(font, head_offset + 18);
  font->locaFormat = geti16(font, head_offset + 50);

  // Read 'hhea' table
  if (gettable(font, "hhea", &hhea_offset) < 0)
    return -1;
  if (!is_safe_offset(font, hhea_offset, 0x24uLL))
    return -1;
    
  font->numLongHmtx = getu16(font, hhea_offset + 34);

  return 0;
}