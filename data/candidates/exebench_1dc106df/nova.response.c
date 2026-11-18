unsigned long i2hs(unsigned int value, char *ptr) {
    char *hex = "0123456789ABCDEF";
    char *hex_begin = ptr;
    *ptr = 0;
    while (value > 0) {
        *ptr++ = hex[value & 0xF];
        value >>= 4;
    }
    if (*ptr == 0)
        *ptr++ = '0';
    *ptr-- = 0;
    char c;
    while ((c = *hex_begin++)!= 0)
        *ptr-- = c;
    return (unsigned long)(ptr + 1);
}