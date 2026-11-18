stbtt_int32 __cdecl stbtt__GetGlyphGPOSInfoAdvance(const stbtt_fontinfo *info, int glyph1, int glyph2)
{
    stbtt_int32 i, sti;
    stbtt_uint8 *data, *lookupList, *lookupTable, *table;
    stbtt_uint16 lookupCount, lookupType, subTableCount;
    stbtt_uint16 posFormat, coverageOffset;
    int coverageIndex;

    if (!info->gpos)
        return 0;

    data = &info->data[info->gpos];

    // Check GPOS table version (1.0 expected)
    if (ttUSHORT(data) != 1 || ttUSHORT(data + 2) != 0)
        return 0;

    lookupList = &data[ttUSHORT(data + 8)];
    lookupCount = ttUSHORT(lookupList);

    for (i = 0; i < lookupCount; ++i)
    {
        lookupTable = &lookupList[ttUSHORT(&lookupList[2 * i + 2])];
        lookupType = ttUSHORT(lookupTable);
        subTableCount = ttUSHORT(lookupTable + 4);

        // LookupType 2: Pair Adjustment Positioning
        if (lookupType != 2)
            continue;

        for (sti = 0; sti < subTableCount; ++sti)
        {
            table = &lookupTable[ttUSHORT(&lookupTable[2 * sti + 6])];
            posFormat = ttUSHORT(table);
            coverageOffset = ttUSHORT(table + 2);
            coverageIndex = stbtt__GetCoverageIndex(&table[coverageOffset], glyph1);

            if (coverageIndex == -1)
                continue;

            // Both formats require valueFormat1 to be exactly 4 (XAdvance) and valueFormat2 to be 0
            if (ttUSHORT(table + 4) != 4 || ttUSHORT(table + 6) != 0)
                return 0;

            // Format 1: Glyph Pairs
            if (posFormat == 1)
            {
                stbtt_uint16 pairSetCount = ttUSHORT(table + 8);
                stbtt_uint8 *pairValueTable;
                stbtt_uint16 pairValueCount;
                stbtt_uint8 *pairValueArray;
                stbtt_int32 l, r, m, straw;

                if (coverageIndex >= pairSetCount)
                    return 0;

                pairValueTable = &table[ttUSHORT(&table[2 * coverageIndex + 10])];
                pairValueCount = ttUSHORT(pairValueTable);
                pairValueArray = pairValueTable + 2;

                // Binary search for glyph2 in the pair value array
                l = 0;
                r = pairValueCount - 1;
                while (l <= r)
                {
                    m = (l + r) >> 1;
                    straw = ttUSHORT(&pairValueArray[4 * m]);

                    if (glyph2 < straw)
                    {
                        r = m - 1;
                    }
                    else if (glyph2 > straw)
                    {
                        l = m + 1;
                    }
                    else // glyph2 == straw
                    {
                        return ttSHORT(&pairValueArray[4 * m + 2]);
                    }
                }
                continue;
            }

            // Format 2: Class Pairs
            if (posFormat == 2)
            {
                stbtt_uint16 classDef1Offset = ttUSHORT(table + 8);
                stbtt_uint16 classDef2Offset = ttUSHORT(table + 10);
                stbtt_uint16 class1Count = ttUSHORT(table + 12);
                stbtt_uint16 class2Count = ttUSHORT(table + 14);
                int glyph1class = stbtt__GetGlyphClass(&table[classDef1Offset], glyph1);
                int glyph2class = stbtt__GetGlyphClass(&table[classDef2Offset], glyph2);

                if (glyph1class < 0 || glyph1class >= class1Count || 
                    glyph2class < 0 || glyph2class >= class2Count)
                    return 0;

                return ttSHORT(&table[2 * class2Count * glyph1class + 16 + 2 * glyph2class]);
            }

            // Unsupported posFormat
            return 0;
        }
    }

    return 0;
}