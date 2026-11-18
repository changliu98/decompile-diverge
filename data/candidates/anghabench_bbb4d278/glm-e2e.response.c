void coap_option_nibble(unsigned int value, uint8_t *nibble) {
    if (value < 0xd) {
        *nibble = (uint8_t)(value & 0xff);
    } else if (value <= 0x10c) {
        *nibble = 0xd;
    } else if (value <= 0x1010c) {
        *nibble = 0xe;
    }
}