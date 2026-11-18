int memcached_udp_set_cookie(uint8_t *buf, size_t len, uint16_t cookie) {
    if (len < 2) {
        return 0;
    }
    
    buf[0] = (uint8_t)(cookie >> 8);
    buf[1] = (uint8_t)(cookie >> 0);
    
    return 0;
}