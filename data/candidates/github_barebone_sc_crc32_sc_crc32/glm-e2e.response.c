Wrapper function
uint32_t sc_crc32(uint32_t crc, const uint8_t *buf, size_t size) {
    return crc32_sw_le(crc, buf, size);
}