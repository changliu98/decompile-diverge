int st_step_search(struct heatshrink_encoder *hse) {
    uint16_t lookahead_size = get_lookahead_size(hse);
    uint16_t input_size = get_input_buffer_size(hse);
    uint16_t buf_size = hse->buf_size; // offset 0x2
    int is_full = can_take_byte(hse) != 0;
    
    uint16_t end = lookahead_size;
    uint16_t start = input_size;
    uint16_t maxlen = is_full ? 1 : input_size;
    
    // If the remaining lookahead is larger than the available input buffer space
    if (end - start > buf_size) {
        return is_full ? 8 : 7;
    }
    
    uint16_t input_offset = hse->input_offset; // offset 0x0
    uint16_t match_maxlen = input_offset + end;
    uint16_t match_start = match_maxlen - lookahead_size;
    uint16_t match_end = start;
    
    // Clamp match_end
    if (input_size - buf_size < start) {
        match_end = input_size - buf_size;
    }
    
    uint16_t match_index = 0;
    uint16_t match_len = find_longest_match(hse, match_start, match_maxlen, match_end, &match_index);
    
    if (match_len == 0xFFFF) {
        hse->buf_size++;
        hse->output_index = 0; // offset 0x4
        return 3;
    } else {
        hse->match_len = match_len; // offset 0x6
        hse->output_index = match_index; // offset 0x4
        return 3;
    }
}