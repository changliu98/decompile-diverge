void faad_resetbits(struct bitfile *ld, int32_t bits) {
    uint32_t words = bits >> 5;          // -0x14
    uint32_t remainder = bits & 0x1f;    // -0x18
    uint32_t tmp;                        // -0x10

    ld->buffer_size = ld->buffer_size - (words << 2);

    if (ld->buffer_size >= 4) {
        tmp = getdword(ld->buffer_orig + (words << 2));
        ld->buffer_size -= 4;
    } else {
        tmp = getdword_n(ld->buffer_orig + (words << 2), ld->buffer_size);
        ld->buffer_size = 0;
    }
    ld->buf = tmp;

    if (ld->buffer_size >= 4) {
        tmp = getdword(ld->buffer_orig + ((words + 1) << 2));
        ld->buffer_size -= 4;
    } else {
        tmp = getdword_n(ld->buffer_orig + ((words + 1) << 2), ld->buffer_size);
        ld->buffer_size = 0;
    }
    ld->bufa = tmp;

    ld->bits_left = 32 - remainder;
    ld->buffer = ld->buffer_orig + ((words + 2) << 2);
    ld->no_more_reading = 0;
}