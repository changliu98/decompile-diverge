uint32_t fnv_32_buf(const void *buf, size_t len, uint32_t hval) {
    const unsigned char *bp = (const unsigned char *)buf;
    const unsigned char *be = bp + len;
    
    while (bp < be) {
        // Equivalent to: hval *= 0x01000193 (FNV prime)
        hval += (hval << 1) + (hval << 4) + (hval << 7) + (hval << 8) + (hval << 24);
        
        // XOR with the next byte
        hval ^= (uint32_t)*bp++;
    }
    
    return hval;
}