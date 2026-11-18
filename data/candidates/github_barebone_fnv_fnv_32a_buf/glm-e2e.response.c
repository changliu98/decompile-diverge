uint32_t fnv_32a_buf(const void *buf, size_t len, uint32_t hval) {
    const unsigned char *bp = (const unsigned char *)buf;
    const unsigned char *be = bp + len;
    
    while (bp < be) {
        hval ^= (uint32_t)*bp++;
        hval += (hval << 1) + (hval << 4) + (hval << 7) + (hval << 8) + (hval << 24);
    }
    
    return hval;
}