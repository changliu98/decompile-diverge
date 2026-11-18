void drwav_s24_to_f32(float *output, unsigned char *input, size_t len) {
    size_t i;

    if (!output ||!input)
        return;

    for (i = 0; i < len; i++) {
        int32_t v = (input[i * 3 + 0] << 8) | input[i * 3 + 1];
        output[i] = (float)(v / 256.0);
    }
}