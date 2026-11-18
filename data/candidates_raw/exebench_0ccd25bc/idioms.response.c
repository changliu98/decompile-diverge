int ucs2_to_utf8(unsigned int *utf8, unsigned char *ucs2, int endianness)
{
    int i;
    unsigned int ucs2int = 0;
    if (endianness != 2 && endianness != 1)
        return -4;
    if (ucs2 == ((void *)0))
        return -1;
    if (utf8 == ((void *)0))
        return -1;
    for (i = 0; i < 4; i++) {
        if (endianness == 2) {
            if (i > 0)
                ucs2int = ucs2int << 8;
            ucs2int = ucs2int | (unsigned int)ucs2[i];
        } else {
            if (i > 0)
                ucs2int = ucs2int >> 8;
            ucs2int = ucs2int | (unsigned int)ucs2[i] << 24;
        }
    }
    if (ucs2int > 0x10ffff)
        return -16;
    if (ucs2int >= 0xd800 && ucs2int <= 0xdfff)
        return -16;
    *utf8 = (unsigned int)ucs2int;
    return 4;
}