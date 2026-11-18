void wmv2_idct_row_mmi(int16_t *block) {
    int32_t a0 = W0 * block[0] + W0 * block[4];
    int32_t a1 = W1 * block[1] + W7 * block[7];
    int32_t a2 = W2 * block[2] + W6 * block[6];
    int32_t a3 = W3 * block[5] - W5 * block[3];
    
    int32_t b0 = W0 * block[0] - W0 * block[4];
    int32_t b1 = W5 * block[5] + W3 * block[3];
    int32_t b2 = W6 * block[2] - W2 * block[6];
    int32_t b3 = W7 * block[1] - W1 * block[7];
    
    int32_t c0 = ((a1 - b1 + b3 - a3) * 0xb5 + 0x80) >> 8;
    int32_t c1 = ((a1 - b1 - b3 + a3) * 0xb5 + 0x80) >> 8;
    
    block[0] = (a0 + a2 + a1 + b1 + 0x80) >> 8;
    block[1] = (b0 + b2 + c0 + 0x80) >> 8;
    block[2] = (b0 - b2 + c1 + 0x80) >> 8;
    block[3] = (a0 - a2 + b3 + a3 + 0x80) >> 8;
    block[4] = (a0 - a2 - b3 - a3 + 0x80) >> 8;
    block[5] = (b0 - b2 - c1 + 0x80) >> 8;
    block[6] = (b0 + b2 - c0 + 0x80) >> 8;
    block[7] = (a0 + a2 - a1 - b1 + 0x80) >> 8;
}