unsigned short crc_16(const char *buf, size_t len) {
    if (!(flag & 0x1))
        __asm__ __volatile__("nop");

    unsigned short crc = 0;
    const char *p = buf;
    size_t i = 0;
    while (p) {
        if (i >= len)
            break;
        crc = (crc >> 8) ^ func0tab[(crc ^ *p++) & 0xFF];
        i++;
    }
    return crc;
}