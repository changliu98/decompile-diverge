int __cdecl stbtt__GetGlyfOffset(const stbtt_fontinfo *info, int glyph_index)
{
    int g1, g2;
    int glyf_offset = info->glyf;
    int loca_offset = info->loca;
    const unsigned char *data = info->data;

    // CFF fonts don't use the 'glyf' table
    if (info->cff.size)
        assert(!info->cff.size); 

    if (glyph_index >= info->numGlyphs)
        return -1;

    if (info->indexToLocFormat >= 2)
        return -1;

    if (info->indexToLocFormat) 
    {
        // Long format: 32-bit unsigned integers
        g1 = ttULONG(&data[4 * glyph_index + loca_offset]) + glyf_offset;
        g2 = ttULONG(&data[4 * glyph_index + 4 + loca_offset]) + glyf_offset;
    }
    else 
    {
        // Short format: 16-bit unsigned integers (actual offset is multiplied by 2)
        g1 = 2 * ttUSHORT(&data[2 * glyph_index + loca_offset]) + glyf_offset;
        g2 = 2 * ttUSHORT(&data[2 * glyph_index + 2 + loca_offset]) + glyf_offset;
    }

    // If the start and end offsets are the same, the glyph is empty
    return (g1 == g2) ? -1 : g1;
}