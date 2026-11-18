heatshrink_decoder *heatshrink_decoder_alloc(unsigned short input_buffer_size,
                                             unsigned char window_sz2,
                                             unsigned char lookahead_sz2) {
    if ((window_sz2 < 5) ||
        (window_sz2 > 15) ||
        (input_buffer_size == 0) ||
        (lookahead_sz2 < 4) ||
        (lookahead_sz2 >= window_sz2)) {
        return NULL;
    }
    size_t buffers_sz = input_buffer_size + (1 << window_sz2);
    size_t sz = sizeof(heatshrink_decoder) + buffers_sz;
    heatshrink_decoder *hsd = malloc(sz);
    if (hsd == NULL) { return NULL; }
    hsd->input_buffer_size = input_buffer_size;
    hsd->window_sz2 = window_sz2;
    hsd->lookahead_sz2 = lookahead_sz2;
    heatshrink_decoder_reset(hsd);
   
                                                                             ;
    return hsd;
}