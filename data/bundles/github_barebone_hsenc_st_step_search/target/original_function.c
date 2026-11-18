static HSE_state st_step_search(heatshrink_encoder *hse) {
    uint16_t window_length = get_input_buffer_size(hse);
    uint16_t lookahead_sz = get_lookahead_size(hse);
    uint16_t msi = hse->match_scan_index;
    LOG("## step_search, scan @ +%d (%d/%d), input size %d\n",
        msi, hse->input_size + msi, 2*window_length, hse->input_size);

    bool fin = is_finishing(hse);
    if (msi > hse->input_size - (fin ? 1 : lookahead_sz)) {
        /* Current search buffer is exhausted, copy it into the
         * backlog and await more input. */
        LOG("-- end of search @ %d\n", msi);
        return fin ? HSES_FLUSH_BITS : HSES_SAVE_BACKLOG;
    }

    uint16_t input_offset = get_input_offset(hse);
    uint16_t end = input_offset + msi;
    uint16_t start = end - window_length;

    uint16_t max_possible = lookahead_sz;
    if (hse->input_size - msi < lookahead_sz) {
        max_possible = hse->input_size - msi;
    }
    
    uint16_t match_length = 0;
    uint16_t match_pos = find_longest_match(hse,
        start, end, max_possible, &match_length);
    
    if (match_pos == MATCH_NOT_FOUND) {
        LOG("ss Match not found\n");
        hse->match_scan_index++;
        hse->match_length = 0;
        return HSES_YIELD_TAG_BIT;
    } else {
        LOG("ss Found match of %d bytes at %d\n", match_length, match_pos);
        hse->match_pos = match_pos;
        hse->match_length = match_length;
        ASSERT(match_pos <= 1 << HEATSHRINK_ENCODER_WINDOW_BITS(hse) /*window_length*/);

        return HSES_YIELD_TAG_BIT;
    }
}