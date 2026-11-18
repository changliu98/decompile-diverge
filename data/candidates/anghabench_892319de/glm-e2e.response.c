void dlfb_dummy_render(unsigned char *buf) {
    *buf++ = 0xaf;
    *buf++ = 0x6a;
    *buf++ = 0x00;
    *buf++ = 0x00;
    *buf++ = 0x00;
    *buf++ = 0x01;
    *buf++ = 0x00;
    *buf++ = 0x00;
    *buf++ = 0x00;
}