uint16_t get_bits(heatshrink_decoder *hsd, uint8_t count) {
    uint16_t accumulator = 0;
    if (count > 15) { return ((uint16_t)-1); }
    if (hsd->input_size == 0 && ((uint16_t)1 << (count - 1)) > hsd->bit_index) {
        return ((uint16_t)-1);
    }
    for (int i = 0; i < count; i++) {

        if (hsd->bit_index == 0) {
            if (hsd->input_size == 0) { return ((uint16_t)-1); }
            hsd->current_byte = ((uint8_t *)&(hsd))[1 + hsd->input_index];
            hsd->input_index++;
            if (hsd->input_index == hsd->input_size) {
                hsd->input_index = 0;
                hsd->input_size = 0;
            }
            hsd->bit_index = 128;
        }

        accumulator <<= 1;
        if (hsd->current_byte & hsd->bit_index) {
            accumulator |= 1;
        }
        hsd->bit_index >>= 1;
    }
    return accumulator;
}