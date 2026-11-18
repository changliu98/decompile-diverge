int isLegalUTF8(const unsigned char *source, int length) {
    int i;
    unsigned char a;
    switch (length) {
        case 4:
            a = source[length-1];
            if (a < 0x80 || a > 0xBF)
                return 0;
        case 3:
            a = source[length-2];
            if (a < 0x80 || a > 0xBF)
                return 0;
        case 2:
            a = source[length-3];
            if (a >= 0xC0)
                return 0;
            if (source[0] == 0xE0) {
                if (a < 0xA0)
                    return 0;
            } else if (source[0] == 0xF0) {
                if (a < 0x90)
                    return 0;
            } else if (source[0] == 0xF4) {
                if (a >= 0x90)
                    return 0;
            } else if (a < 0x80) {
                return 0;
            }
        case 1:
            if (source[0] >= 0x80 && source[0] <= 0xC1)
                return 0;
            if (source[0] >= 0xF5)
                return 0;
            break;
        default:
            return 0;
    }
    return 1;
}