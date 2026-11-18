int init_font(SFT_Font *font) {
    long head_offset;
    long hhea_offset;

    // Check if the font has at least 12 bytes available
    if (!is_safe_offset(font, 0, 12)) {
        return -1;
    }

    // Check the sfVersion (offset 0). Valid values are 0x00010000 (TrueType)
    // or 'true' (0x74727565). 'OTTO' (0x4F54544F) would fail this check.
    uint32_t sfVersion = getu32(font, 0);
    if (sfVersion != 0x10000 && sfVersion != 0x74727565) {
        return -1;
    }

    // Find the 'head' table
    if (gettable(font, head_tag, &head_offset) < 0) {
        return -1;
    }

    // Check if the 'head' table is at least 54 bytes long
    if (!is_safe_offset(font, head_offset, 54)) {
        return -1;
    }

    // Read unitsPerEm from 'head' table (offset 18)
    font->unitsPerEm = getu16(font, head_offset + 18);

    // Read ascent from 'head' table (offset 50)
    font->ascent = getu16(font, head_offset + 50);

    // Find the 'hhea' table
    if (gettable(font, hhea_tag, &hhea_offset) < 0) {
        return -1;
    }

    // Check if the 'hhea' table is at least 36 bytes long
    if (!is_safe_offset(font, hhea_offset, 36)) {
        return -1;
    }

    // Read descent from 'hhea' table (offset 34)
    font->descent = getu16(font, hhea_offset + 34);

    return 0;
}