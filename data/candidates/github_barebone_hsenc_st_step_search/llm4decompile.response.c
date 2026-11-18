HSE_state st_step_search(heatshrink_encoder *hse) {
    uint16_t match_pos;
    uint16_t match_length;
    uint16_t max_possible;
    uint16_t start;
    uint16_t end;
    uint16_t input_offset;
    uint16_t window_length = get_input_buffer_size(hse);
    uint16_t lookahead_sz = get_lookahead_size(hse);
    uint16_t msi = hse->match_scan_index;
    uint16_t fin = is_finishing(hse) ? 1 : 0;






    if (msi > (hse->input_size - (lookahead_sz - fin))) {
        if (fin) {
            return HSES_FLUSH_BITS;
        } else {
            return HSES_SAVE_BACKLOG;
        }
    }






    input_offset = get_input_offset(hse);
    end = input_offset + msi;
    start = end - window_length;






    max_possible = lookahead_sz;
    if ((hse->input_size - msi) < lookahead_sz) {
        max_possible = hse->input_size - msi;
    }






    match_length = 0;
    match_pos = find_longest_match(hse, start, end, max_possible, &match_length);






    if (match_pos == 0xFFFF) {
        hse->match_scan_index++;
        hse->match_length = 0;
        return HSES_YIELD_TAG_BIT;
    } else {
        hse->match_pos = match_pos;
        hse->match_length = match_length;
        return HSES_YIELD_TAG_BIT;
    }
}