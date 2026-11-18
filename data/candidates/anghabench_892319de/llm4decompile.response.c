char *dlfb_dummy_render(char *buf)
{
    buf[0] = 0xaf;
    buf[1] = 0x6a;
    buf[2] = 0x00;
    buf[3] = 0x00;
    buf[4] = 0x00;
    buf[5] = 0x01;
    buf[6] = 0x00;
    buf[7] = 0x00;
    buf[8] = 0x00;
    return buf + 9;
}