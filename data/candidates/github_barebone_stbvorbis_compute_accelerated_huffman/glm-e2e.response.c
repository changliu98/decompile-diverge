void compute_accelerated_huffman(struct huffman *h) {
    for (int i = 0; i < 0x400; i++) {
        h->accel_table[i] = 0xffff;
    }

    int max_len = h->is_accelerated ? h->accel_values[0] : h->base_values[0];
    int limit = max_len > 0x7fff ? 0x7fff : max_len;

    for (int i = 0; i < limit; i++) {
        if (h->lengths[i] > 0xa) {
            continue;
        }

        int code = h->is_accelerated ? float32_unpack(h->accel_values[i]) : h->base_values[i];
        
        while (code < 0x400) {
            h->accel_table[code] = (int16_t)i;
            code += 1 << h->lengths[i];
        }
    }
}