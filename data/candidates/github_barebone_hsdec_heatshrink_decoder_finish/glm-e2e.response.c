int heatshrink_decoder_finish(struct heatshrink_decoder *hsd) {
    int res;

    if (hsd == NULL) {
        res = -1;
    } else {
        uint8_t state = hsd->state;
        
        if (state == 0) {
            res = (hsd->output_count == 0) ? 1 : 0;
        } else if (state == 1) {
            res = (hsd->output_count == 0) ? 1 : 0;
        } else if (state == 2 || state == 3 || state == 4 || state == 5) {
            res = (hsd->output_count == 0) ? 1 : 0;
        } else {
            res = 1;
        }
    }
    
    return res;
}