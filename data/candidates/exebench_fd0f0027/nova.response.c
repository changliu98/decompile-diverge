void ltostr(unsigned int num, char *buf) {
    int i = 0;
    buf[0] = '\0';
    buf[8] = '\0';
    for (i = 0; i < 8; i++) {
        int digit = num & 0xF;
        digit += '0';
        if (digit > '9')
            digit += 7;
        buf[7 - i] = digit;
        num >>= 4;
    }
}