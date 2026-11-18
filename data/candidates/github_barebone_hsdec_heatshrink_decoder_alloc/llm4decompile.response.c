heatshrink_decoder *heatshrink_decoder_alloc(uint16_t input_buffer_size,
                                            uint8_t window_sz2,
                                            uint8_t lookahead_sz2) {
    if ((window_sz2 < 4) ||
        (window_sz2 > 15) ||
        (input_buffer_size == 0) ||
        (lookahead_sz2 < 3) ||
        (lookahead_sz2 >= window_sz2)) {
        return NULL;
    }
    size_t buffers_sz = (1 << window_sz2) + input_buffer_size;
    size_t sz = sizeof(heatshrink_decoder) + buffers_sz;
    heatshrink_decoder *hsd = malloc(sz);
    if (hsd == NULL) { return NULL; }
    hsd->input_buffer_size = input_buffer_size;
    hsd->window_sz2 = window_sz2;
    hsd->lookahead_sz2 = lookahead_sz2;
    heatshrink_decoder_reset(hsd);
    (void)buffers_sz;
    return hsd;
}