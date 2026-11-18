int stbtt__GetGlyphClass(const uint8_t *table, int glyph) {
    int result;
    uint16_t classFormat = ttUSHORT(table);

    switch (classFormat) {
        case 1: {
            uint16_t startGlyphID = ttUSHORT(table + 2);
            uint16_t glyphCount = ttUSHORT(table + 4);
            const uint8_t *classValues = table + 6;
            
            if (glyph >= startGlyphID && glyph < startGlyphID + glyphCount) {
                result = ttUSHORT(classValues + (glyph - startGlyphID) * 2);
                return result;
            }
            break;
        }
        case 2: {
            uint16_t classRangeCount = ttUSHORT(table + 2);
            const uint8_t *classRangeRecords = table + 4;
            
            int low = 0;
            int high = classRangeCount - 1;
            
            while (low <= high) {
                int mid = low + (high - low) / 2;
                const uint8_t *record = classRangeRecords + mid * 6;
                
                uint16_t startGlyphID = ttUSHORT(record);
                uint16_t endGlyphID = ttUSHORT(record + 2);
                
                if (glyph < startGlyphID) {
                    high = mid - 1;
                } else if (glyph > endGlyphID) {
                    low = mid + 1;
                } else {
                    result = ttUSHORT(record + 4);
                    return result;
                }
            }
            break;
        }
        default:
            result = -1;
            return result;
    }
    
    result = 0;
    return result;
}