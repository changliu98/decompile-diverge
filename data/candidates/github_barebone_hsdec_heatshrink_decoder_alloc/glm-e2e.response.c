struct heatshrink_decoder *heatshrink_decoder_alloc(unsigned short input_buffer_size, unsigned char window_sz2, unsigned char lookahead_sz2) {
    struct heatshrink_decoder *hd;
    unsigned long alloc_size;

    // Validate arguments
    if (window_sz2 < 4 || window_sz2 > 15) {
        return NULL;
    }
    if (input_buffer_size == 0) {
        return NULL;
    }
    if (lookahead_sz2 < 3 || lookahead_sz2 >= window_sz2) {
        return NULL;
    }

    // Calculate allocation size: (1 << window_sz2) + input_buffer_size + 18
    alloc_size = (1UL << window_sz2) + input_buffer_size + 18;

    // Allocate memory (the call at 0x92 abstracts malloc + reset/init)
    hd = heatshrink_decoder_alloc_and_init(alloc_size);
    if (hd == NULL) {
        return NULL;
    }

    // Initialize fields
    hd->input_buffer_size = input_buffer_size;
    hd->window_sz2 = window_sz2;
    hd->lookahead_sz2 = lookahead_sz2;

    // Call reset/finish init function
    heatshrink_decoder_init(hd);

    return hd;
}