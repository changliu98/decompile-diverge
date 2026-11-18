int stbtt__GetGlyphGPOSInfoAdvance(const stbtt_fontinfo *info, int glyph1, int glyph2) {
    const uint8_t *base = info->data + info->gpos;

    // Validate GPOS header version and script list offset
    if (ttUSHORT(base) != 1) return 0;
    if (ttUSHORT(base + 2) != 0) return 0;

    uint16_t lookup_list_offset = ttUSHORT(base + 8);
    const uint8_t *lookup_list = base + lookup_list_offset;
    uint16_t lookup_count = ttUSHORT(lookup_list);

    for (int i = 0; i < lookup_count; i++) {
        uint16_t lookup_offset = ttUSHORT(lookup_list + 2 + i * 2);
        const uint8_t *lookup = lookup_list + lookup_offset;
        uint16_t lookup_type = ttUSHORT(lookup);
        uint16_t subtable_count = ttUSHORT(lookup + 4);
        const uint8_t *subtable_offsets = lookup + 6;

        // Type 2: PairPos (Pair Adjustment Positioning)
        if (lookup_type != 2) continue;

        for (int j = 0; j < subtable_count; j++) {
            uint16_t subtable_offset = ttUSHORT(subtable_offsets + j * 2);
            const uint8_t *subtable = lookup + subtable_offset;
            uint16_t pos_format = ttUSHORT(subtable);
            uint16_t coverage_offset = ttUSHORT(subtable + 2);

            int coverage_index = stbtt__GetCoverageIndex(subtable + coverage_offset, glyph1);
            if (coverage_index == -1) continue;

            if (pos_format == 1) {
                // Format 1: Adjustments for Glyph Pairs
                uint16_t pair_set_count = ttUSHORT(subtable + 4);
                uint16_t pair_set_offset = ttUSHORT(subtable + 6 + coverage_index * 2);
                const uint8_t *pair_set = subtable + pair_set_offset;
                uint16_t pair_value_count = ttUSHORT(pair_set);
                const uint8_t *pair_value_records = pair_set + 2;

                if (coverage_index >= pair_set_count) return 0;

                // Binary search for glyph2 in the pair value records
                int low = 0;
                int high = pair_value_count - 1;
                while (low <= high) {
                    int mid = low + (high - low) / 2;
                    const uint8_t *pair_value_record = pair_value_records + mid * 4; // 2 (glyph) + 2 (valueRecord)
                    uint16_t second_glyph = ttUSHORT(pair_value_record);
                    
                    if (glyph2 < second_glyph) {
                        high = mid - 1;
                    } else if (glyph2 > second_glyph) {
                        low = mid + 1;
                    } else {
                        // Found match, return valueRecord1 (advance adjustment)
                        return ttSHORT(pair_value_record + 2);
                    }
                }
            } else if (pos_format == 2) {
                // Format 2: Class-Based Pair Positioning
                uint16_t class_def1_offset = ttUSHORT(subtable + 4);
                uint16_t class_def2_offset = ttUSHORT(subtable + 6);
                int class1 = stbtt__GetGlyphClass(subtable + class_def1_offset, glyph1);
                int class2 = stbtt__GetGlyphClass(subtable + class_def2_offset, glyph2);
                
                uint16_t class1_count = ttUSHORT(subtable + 8);
                uint16_t class2_count = ttUSHORT(subtable + 10);

                if (class1 < 0 || class1 >= class1_count) return 0;
                if (class2 < 0 || class2 >= class2_count) return 0;

                const uint8_t *class1_records = subtable + 12;
                const uint8_t *class1_record = class1_records + (class1 * class2_count) * 2; // 2 bytes per valueRecord
                const uint8_t *class2_record = class1_record + class2 * 2;

                return ttSHORT(class2_record);
            } else {
                return 0; // Unknown format
            }
        }
    }

    return 0;
}