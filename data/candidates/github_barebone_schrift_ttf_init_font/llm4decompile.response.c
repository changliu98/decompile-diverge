int init_font(SFT_Font *font)
{
    uint32_t head, hhea;
    uint32_t scalerType;

    if (!is_safe_offset(font, 0, 12))
        return -1;

    scalerType = getu32(font, 0);
    if (scalerType != 0x10000 && scalerType != 0x74727565)
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