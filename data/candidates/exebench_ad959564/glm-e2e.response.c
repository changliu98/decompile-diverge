int do_map(char *out, int flags, char c) {
    int ret;
    char ch = c;
    int val = (int)(signed char)c;

    if (val == 0x8) {
        if (flags & 0x80) {
            *out = 0x7f;
            ret = 1;
        } else {
            *out = ch;
            ret = 1;
        }
    } else if (val == 0xa) {
        if (flags & 0x8) {
            *out = 0xd;
            ret = 1;
        } else if (flags & 0x10) {
            *out = 0xd;
            *(out + 1) = 0xa;
            ret = 2;
        } else if (flags & 0x20) {
            ret = 0;
        } else {
            *out = ch;
            ret = 1;
        }
    } else if (val == 0xd) {
        if (flags & 0x1) {
            *out = 0xa;
            ret = 1;
        } else if (flags & 0x2) {
            *out = 0xd;
            *(out + 1) = 0xa;
            ret = 2;
        } else if (flags & 0x4) {
            ret = 0;
        } else {
            *out = ch;
            ret = 1;
        }
    } else if (val == 0x7f) {
        if (flags & 0x40) {
            *out = 0x8;
            ret = 1;
        } else {
            *out = ch;
            ret = 1;
        }
    } else {
        *out = ch;
        ret = 1;
    }

    return ret;
}