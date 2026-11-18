static int func0(int c) {
    int ret;
    unsigned int uc = c;
    if (uc) {
        while (uc >= 0x100) {
            uc -= 0x100;
        }
        while (uc >= 0x80) {
            uc -= 0x80;
        }
        while (uc >= 0x40) {
            uc -= 0x40;
        }
        while (uc >= 0x20) {
            uc -= 0x20;
        }
        while (uc >= 0x10) {
            uc -= 0x10;
        }
        while (uc >= 0x8) {
            uc -= 0x8;
        }
        while (uc >= 0x4) {
            uc -= 0x4;
        }
        while (uc >= 0x2) {
            uc -= 0x2;
        }
        while (uc >= 0x1) {
            uc -= 0x1;
        }
        if (uc == 0x100) {
            ret = 0x7f;
        } else if (uc == 0x101) {
            ret = 0x24;
        } else if (uc == 0x102) {
            ret = 0x25;
        } else if (uc == 0x103) {
            ret = 0x26;
        } else if (uc == 0x104) {
            ret = 0x27;
        } else if (uc == 0x105) {
            ret = 0x28;
        } else if (uc == 0x106) {
            ret = 0x29;
        } else if (uc == 0x107) {
            ret = 0x2a;
        } else if (uc == 0x108) {
            ret = 0x2b;
        } else if (uc == 0x109) {
            ret = 0x2c;
        } else if (uc == 0x10a) {