static void mult121665(uint32_t *output, uint32_t *input) {
    uint32_t acc = 0;
    uint32_t i;

    for (i = 0; i < 32; i++) {
        acc += input[i];
        output[i] = acc & 0xFF;
        acc >>= 8;
    }

    acc += input[32];
    output[32] = acc & 0x7F;
    acc >>= 7;

    for (i = 0; i < 32; i++) {
        acc += output[i];
        output[i] = acc & 0xFF;
        acc >>= 8;
    }

    output[i] = acc;
}