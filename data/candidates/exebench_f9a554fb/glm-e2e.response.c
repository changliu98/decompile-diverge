void dlsch_MRC_relay_LLR(short *dst, unsigned int length, short *src) {
    for (unsigned int i = 0; i < length; i++) {
        dst[i] += src[i];
    }
}