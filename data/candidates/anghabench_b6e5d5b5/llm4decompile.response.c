void packInt32(uint8_t *buf, int32_t i) {
    buf[0] = (uint8_t)i;
    buf[1] = (uint8_t)(i >> 8);
    buf[2] = (uint8_t)(i >> 16);
    buf[3] = (uint8_t)(i >> 24);
}