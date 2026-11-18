static int isLegalUTF8(unsigned char *source, int length)
{
    unsigned char a;
    unsigned char *srcptr = source + length;
    int ret;

    switch (length) {
    default: ret = 0; break;
    case 4: if ((a = (*--srcptr)) < 0x80 || a > 0xBF) { ret = 0; break; }
    case 3: if ((a = (*--srcptr)) < 0x80 || a > 0xBF) { ret = 0; break; }
    case 2: if ((a = (*--srcptr)) > 0xBF) { ret = 0; break; }
        switch (*source) {

            case 0xE0: if (a < 0xA0) { ret = 0; break; }
            case 0xF0: if (a < 0x90) { ret = 0; break; }
            case 0xF4: if (a > 0x8F) { ret = 0; break; }
            case 0xF5:
            default: if (a < 0x80) { ret = 0; break; }
        }
    case 1: if (*source >= 0x80 && *source < 0xC2) { ret = 0; break; }
        if (*source > 0xF4) { ret = 0; break; }
    case 0: ret = 1;
    }

    return ret;
}