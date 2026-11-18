void _prtX16(uint32_t num, char *str)
{
    static const char *digits = "0123456789ABCDEF";
    char buf[9];
    int i;

    buf[0] = '\0';
    for (i = 1; i < 9; i++) {
        buf[i] = digits[num & 0x0F];
        num >>= 4;
    }

    for (i = 8; i > 0; i--) {
        if (buf[i] != '0')
            break;
    }

    if (i == 0)
        i = 1;

    while (i >= 0) {
        *str++ = buf[i];
        i--;
    }
}