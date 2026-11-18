void SHUF(const uint8_t *src, uint8_t *dst) {
    dst[0]  = src[8];
    dst[1]  = src[11];
    dst[2]  = src[12];
    dst[3]  = src[15];
    dst[4]  = src[2];
    dst[5]  = src[1];
    dst[6]  = src[6];
    dst[7]  = src[5];
    dst[8]  = src[10];
    dst[9]  = src[9];
    dst[10] = src[14];
    dst[11] = src[13];
    dst[12] = src[0];
    dst[13] = src[7];
    dst[14] = src[4];
    dst[15] = src[3];
}