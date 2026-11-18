int dv_write_ssyb_id(uint8_t id, uint8_t dsf, uint8_t *buf) {
    if (id == 0x00 || id == 0x06) {
        buf[0] = (dsf << 7) | 0x0f;
    } else if (id == 0x0b) {
        buf[0] = (dsf << 7) | 0x7f;
    } else {
        buf[0] = (dsf << 7) | 0x0f;
    }
    
    buf[1] = (id & 0x0f) | 0xf0;
    buf[2] = 0xff;
    
    return 3;
}