heatshrink_decoder * __cdecl heatshrink_decoder_alloc(
        uint16_t input_buffer_size, 
        uint8_t window_sz2, 
        uint8_t lookahead_sz2) 
{
    heatshrink_decoder *hsd;

    // Validate input parameters
    if (window_sz2 < 4 || 
        window_sz2 > 15 || 
        input_buffer_size == 0 || 
        lookahead_sz2 < 3 || 
        lookahead_sz2 >= window_sz2) 
    {
        return NULL;
    }

    // Allocate memory for the decoder struct, the window, and the input buffer
    hsd = (heatshrink_decoder *)malloc(sizeof(heatshrink_decoder) + (1 << window_sz2) + input_buffer_size);
    if (hsd == NULL) {
        return NULL;
    }

    // Initialize fields
    hsd->input_buffer_size = input_buffer_size;
    hsd->window_sz2 = window_sz2;
    hsd->lookahead_sz2 = lookahead_sz2;

    heatshrink_decoder_reset(hsd);
    
    return hsd;
}