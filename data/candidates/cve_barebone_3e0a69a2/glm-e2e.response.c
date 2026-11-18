void read_quant_matrix_ext(void *matrix, void *s) {
    int i;
    int val;
    int pos;

    if (get_bits1(s)) {
        for (i = 0; i < 64; i++) {
            val = get_bits(s, 8);
            pos = matrix[ff_zigzag_direct[i]];
            *(uint16_t *)((char *)matrix + 0x40 + pos * 2) = (uint16_t)val;
            *(uint16_t *)((char *)matrix + 0xc0 + pos * 2) = (uint16_t)val;
        }
    }

    if (get_bits1(s)) {
        for (i = 0; i < 64; i++) {
            get_bits(s, 8);
        }
    }

    if (get_bits1(s)) {
        for (i = 0; i < 64; i++) {
            val = get_bits(s, 8);
            pos = matrix[ff_zigzag_direct[i]];
            *(uint16_t *)((char *)matrix + 0xc0 + pos * 2) = (uint16_t)val;
        }
    }

    if (get_bits1(s)) {
        for (i = 0; i < 64; i++) {
            get_bits(s, 8);
        }
    }

    next_start_code_studio(s);
}