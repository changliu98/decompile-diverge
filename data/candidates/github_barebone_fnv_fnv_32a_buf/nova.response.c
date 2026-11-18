static uint32_t fnv_32a_buf(const unsigned char *p, size_t len, uint32_t crc) {
    unsigned char *ubuf = (unsigned char *) p;
    unsigned char *ubufend = ubuf + len;

    for (; ubuf < ubufend; ubuf++) {
        crc = crc ^ (*ubuf);
        for (int i = 0; i < 8; i++) {
            crc = (crc << 1) ^ ((crc & 0x80)? 0x1d : 0);
        }
    }

    return crc;
}