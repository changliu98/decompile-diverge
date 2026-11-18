stbtt_int32 __cdecl stbtt__GetCoverageIndex(stbtt_uint8 *coverageTable, int glyph)
{
    int coverageFormat = ttUSHORT(coverageTable);
    
    // Format 1: Coverage table consists of an array of glyph indices
    if (coverageFormat == 1)
    {
        int l = 0;
        int r = ttUSHORT(coverageTable + 2) - 1; // Glyph count - 1
        
        while (l <= r)
        {
            int m = (l + r) >> 1;
            int straw = ttUSHORT(&coverageTable[2 * m + 4]); // 2 bytes per glyph + 4 byte header
            
            if (glyph < straw)
            {
                r = m - 1;
            }
            else if (glyph > straw)
            {
                l = m + 1;
            }
            else
            {
                return m; // Glyph found, index is its position in the array
            }
        }
        return -1;
    }
    
    // Format 2: Coverage table consists of an array of glyph ranges
    if (coverageFormat == 2)
    {
        int l = 0;
        int r = ttUSHORT(coverageTable + 2) - 1; // Range count - 1
        
        while (l <= r)
        {
            int m = (l + r) >> 1;
            stbtt_uint8 *rangeRecord = &coverageTable[6 * m + 4]; // 6 bytes per range + 4 byte header
            
            int strawStart = ttUSHORT(rangeRecord);
            int strawEnd = ttUSHORT(rangeRecord + 2);
            
            if (glyph < strawStart)
            {
                r = m - 1;
            }
            else if (glyph > strawEnd)
            {
                l = m + 1;
            }
            else
            {
                // Glyph found, index is calculated from the start of the range
                int startCoverageIndex = ttUSHORT(rangeRecord + 4);
                return glyph - strawStart + startCoverageIndex;
            }
        }
        return -1;
    }
    
    // Unsupported coverage format
    return -1;
}