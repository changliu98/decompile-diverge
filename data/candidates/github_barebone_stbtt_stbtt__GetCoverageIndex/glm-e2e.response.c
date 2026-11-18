int stbtt__GetCoverageIndex(stbtt_uint8p coverageTable, int glyph) {
    int result = -1;
    int format = ttUSHORT(coverageTable);

    if (format == 1) {
        // Format 1: List of individual glyph indices
        int count = ttUSHORT(coverageTable + 2);
        int low = 0;
        int high = count - 1;

        while (low <= high) {
            int mid = low + (high - low) / 2;
            int glyph_id = ttUSHORT(coverageTable + 4 + mid * 2);

            if (glyph < glyph_id) {
                high = mid - 1;
            } else if (glyph > glyph_id) {
                low = mid + 1;
            } else {
                result = mid;
                goto done;
            }
        }
        result = -1;
    } else if (format == 2) {
        // Format 2: List of glyph ranges
        int rangeCount = ttUSHORT(coverageTable + 2);
        stbtt_uint8p rangeBase = coverageTable + 4;
        int low = 0;
        int high = rangeCount - 1;

        while (low <= high) {
            int mid = low + (high - low) / 2;
            stbtt_uint8p range = rangeBase + mid * 6;
            
            int startGlyph = ttUSHORT(range);
            int endGlyph = ttUSHORT(range + 2);

            if (glyph < startGlyph) {
                high = mid - 1;
            } else if (glyph > endGlyph) {
                low = mid + 1;
            } else {
                int startCoverageIndex = ttUSHORT(range + 4);
                result = startCoverageIndex + glyph - startGlyph;
                goto done;
            }
        }
        result = -1;
    } else {
        // Unsupported format
        result = -1;
    }

done:
    return result;
}