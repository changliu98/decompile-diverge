static int
get_char_utf8(int *uc, unsigned char *buf)
{
    int c1, c2, c3, c4, c5, c6;
    int n;

    c1 = buf[0];
    if ((c1 & 0x80) == 0) {
        *uc = c1;
        n = (c1 == 0 ? 0 : 1);
    } else if ((c1 & 0x40) == 0) {
        *uc = -1;
        n = -1;
    } else {
        c2 = buf[1];
        if ((c2 & 0xc0) != 0x80) {
            *uc = -1;
            n = -1;
        } else if ((c1 & 0x20) == 0) {
            if ((c1 & 0x1e) < 1) {
                *uc = -1;
                n = -1;
            } else {
                *uc = ((c1 & 0x1f) << 6) | (c2 & 0x3f);
                n = 2;
            }
        } else {
            c3 = buf[2];
            if ((c3 & 0xc0) != 0x80) {
                *uc = -1;
                n = -1;
            } else if ((c1 & 0x10) == 0) {
                if (((c1 & 0x0f) | (c2 & 0x20)) < 1) {
                    *uc = -1;
                    n = -1;
                } else {
                    *uc = ((c1 & 0x0f) << 12) | ((c2 & 0x3f) << 6) | (c3 & 0x3f);
                    n = 3;
                }
            } else {
                c4 = buf[3];
                if ((c4 & 0xc0) != 0x80) {
                    *uc = -1;
                    n = -1;
                } else if ((c1 & 0x08) == 0) {
                    if (((c1 & 0x07) | (c2 & 0x30)) < 1) {
                        *uc = -1;
                        n = -1;
                    } else {
                        *uc = ((c1 & 0x07) << 18) | ((c2 & 0x3f) << 12) |
                            ((c3 & 0x3f) << 6) | (c4 & 0x3f);
                        n = 4;
                    }
                } else {
                    c5 = buf[4];
                    if ((c5 & 0xc0) != 0x80) {
                        *uc = -1;
                        n = -1;
                    } else if ((c1 & 0x04) == 0) {
                        if (((c1 & 0x03) | (c2 & 0x38)) < 1) {
                            *uc = -1;
                            n = -1;
                        } else {
                            *uc = ((c1 & 0x03) << 24) | ((c2 & 0x3f) << 18) |
                                ((c3 & 0x3f) << 12) | ((c4 & 0x3f) << 6) |
                                (c5 & 0x3f);
                            n = 5;
                        }
                    } else {
                        c6 = buf[5];
                        if ((c6 & 0xc0) != 0x80) {
                            *uc = -1;
                            n = -1;
                        } else if ((c1 & 0x02) == 0) {
                            if (((c1 & 0x01) | (c2 & 0x3c)) < 1) {
                                *uc = -1;
                                n = -1;
                            } else {
                                *uc = ((c1 & 0x01) << 30) | ((c2 & 0x3f) << 24) |
                                    ((c3 & 0x3f) << 18) | ((c4 & 0x3f) << 12) |
                                    ((c5 & 0x3f) << 6) | (c6 & 0x3f);
                                n = 6;
                            }
                        } else {
                            *uc = -1;
                            n = -1;
                        }
                    }
                }
            }
        }
    }
    return n;
}