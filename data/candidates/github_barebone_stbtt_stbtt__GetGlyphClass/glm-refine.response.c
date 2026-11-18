stbtt_int32 __cdecl stbtt__GetGlyphClass(stbtt_uint8 *classDefTable, int glyph)
{
    stbtt_uint16 classFormat = ttUSHORT(classDefTable);

    // ClassDefFormat 1: Array of class values for a contiguous range of glyphs
    if (classFormat == 1)
    {
        stbtt_uint16 startGlyphID = ttUSHORT(classDefTable + 2);
        stbtt_uint16 glyphCount = ttUSHORT(classDefTable + 4);

        if (glyph >= startGlyphID && glyph < startGlyphID + glyphCount)
        {
            return ttUSHORT(classDefTable + 6 + 2 * (glyph - startGlyphID));
        }
        return 0;
    }

    // ClassDefFormat 2: Array of ClassRangeRecords, searched via binary search
    if (classFormat == 2)
    {
        stbtt_int32 left = 0;
        stbtt_int32 right = ttUSHORT(classDefTable + 2) - 1;

        while (left <= right)
        {
            stbtt_int32 mid = (left + right) >> 1;
            stbtt_uint8 *classRangeRecord = classDefTable + 4 + 6 * mid;
            
            stbtt_uint16 rangeStart = ttUSHORT(classRangeRecord);
            stbtt_uint16 rangeEnd = ttUSHORT(classRangeRecord + 2);

            if (glyph < rangeStart)
            {
                right = mid - 1;
            }
            else if (glyph > rangeEnd)
            {
                left = mid + 1;
            }
            else // rangeStart <= glyph <= rangeEnd
            {
                return ttUSHORT(classRangeRecord + 4);
            }
        }
        return 0;
    }

    // Unknown format
    return -1;
}