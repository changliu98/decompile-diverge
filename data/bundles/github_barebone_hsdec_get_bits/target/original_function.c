static uint16_t get_bits(heatshrink_decoder *hsd, uint8_t count) {
    uint16_t accumulator = 0;
    int i = 0;
    if (count > 15) { return NO_BITS; }
    LOG("-- popping %u bit(s)\n", count);

    /* If we aren't able to get COUNT bits, suspend immediately, because we
     * don't track how many bits of COUNT we've accumulated before suspend. */
    if (hsd->input_size == 0) {
        if (hsd->bit_index < (1 << (count - 1))) { return NO_BITS; }
    }

    for (i = 0; i < count; i++) {
        if (hsd->bit_index == 0x00) {
            if (hsd->input_size == 0) {
                LOG("  -- out of bits, suspending w/ accumulator of %u (0x%02x)\n",
                    accumulator, accumulator);
                return NO_BITS;
            }
            hsd->current_byte = hsd->buffers[hsd->input_index++];
            LOG("  -- pulled byte 0x%02x\n", hsd->current_byte);
            if (hsd->input_index == hsd->input_size) {
                hsd->input_index = 0; /* input is exhausted */
                hsd->input_size = 0;
            }
            hsd->bit_index = 0x80;
        }
        accumulator <<= 1;
        if (hsd->current_byte & hsd->bit_index) {
            accumulator |= 0x01;
            if (0) {
                LOG("  -- got 1, accumulator 0x%04x, bit_index 0x%02x\n",
                accumulator, hsd->bit_index);
            }
        } else {
            if (0) {
                LOG("  -- got 0, accumulator 0x%04x, bit_index 0x%02x\n",
                accumulator, hsd->bit_index);
            }
        }
        hsd->bit_index >>= 1;
    }

    if (count > 1) { LOG("  -- accumulated %08x\n", accumulator); }
    return accumulator;
}