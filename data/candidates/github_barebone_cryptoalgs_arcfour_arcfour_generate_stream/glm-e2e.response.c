void arcfour_generate_stream(uint8_t *state, uint8_t *out_stream, uint64_t length) {
    uint64_t i = 0;
    int32_t x = 0;
    int32_t y = 0;

    while (i < length) {
        x = (x + 1) % 256;
        y = (y + state[x]) % 256;
        
        uint8_t temp = state[x];
        state[x] = state[y];
        state[y] = temp;
        
        uint8_t xor_byte = state[(state[x] + state[y]) % 256];
        out_stream[i] = xor_byte;
        
        i++;
    }
}