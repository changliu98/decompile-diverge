int uniphier_ld11_get_gpio_muxval(int port, int pin) {
    int muxval;
    
    if (pin == 0x84 || pin == 0x87) {
        muxval = 0xd;
    } else if (pin >= 0x78 && pin <= 0x8f) {
        muxval = 0xe;
    } else {
        muxval = 0xf;
    }
    
    return muxval;
}