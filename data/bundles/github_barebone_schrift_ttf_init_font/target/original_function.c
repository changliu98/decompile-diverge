static int
init_font(SFT_Font *font)
{
	uint_fast32_t scalerType, head, hhea;

	if (!is_safe_offset(font, 0, 12))
		return -1;
	/* Check for a compatible scalerType (magic number). */
	scalerType = getu32(font, 0);
	if (scalerType != FILE_MAGIC_ONE && scalerType != FILE_MAGIC_TWO)
		return -1;

	if (gettable(font, "head", &head) < 0)
		return -1;
	if (!is_safe_offset(font, head, 54))
		return -1;
	font->unitsPerEm = getu16(font, head + 18);
	font->locaFormat = geti16(font, head + 50);
	
	if (gettable(font, "hhea", &hhea) < 0)
		return -1;
	if (!is_safe_offset(font, hhea, 36))
		return -1;
	font->numLongHmtx = getu16(font, hhea + 34);

	return 0;
}