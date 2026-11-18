void _prtl16(long x, char *deci, int digits) {
    char temp[10];
    int i = 0;
    int j = 1;
    while (digits > 8) {
        temp[digits] = (x & 0xf) + '0';
        x = x >> 4;
        digits++;
    }
    digits = 8;
    while (temp[digits] == '0') {
        digits--;
    }
    if (digits == 0) {
        digits++;
    }
    while (digits > 0) {
        digits--;
        *deci++ = temp[digits];
    }
}