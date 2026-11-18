int utf8uprcodepoint(int cp) {
    if (cp >= 0x61 && cp <= 0x7a) {
        cp -= 0x20;
    } else if (cp >= 0xe0 && cp <= 0xf6) {
        cp -= 0x20;
    } else if (cp >= 0xf8 && cp <= 0xfe) {
        cp -= 0x20;
    } else if (cp >= 0x3b1 && cp <= 0x3c1) {
        cp -= 0x20;
    } else if (cp >= 0x3c3 && cp <= 0x3cb) {
        cp -= 0x20;
    } else if (cp >= 0x430 && cp <= 0x44f) {
        cp -= 0x20;
    } else if (cp >= 0x450 && cp <= 0x45f) {
        cp -= 0x50;
    } else if ((cp >= 0x100 && cp <= 0x12f) ||
               (cp >= 0x132 && cp <= 0x137) ||
               (cp >= 0x14a && cp <= 0x177) ||
               (cp >= 0x182 && cp <= 0x185) ||
               (cp >= 0x1a0 && cp <= 0x1a5) ||
               (cp >= 0x1de && cp <= 0x1ef) ||
               (cp >= 0x1f8 && cp <= 0x21f) ||
               (cp >= 0x222 && cp <= 0x233) ||
               (cp >= 0x246 && cp <= 0x24f) ||
               (cp >= 0x3d8 && cp <= 0x3ef) ||
               (cp >= 0x460 && cp <= 0x481) ||
               (cp >= 0x48a && cp <= 0x4ff)) {
        cp &= 0xfffffffe;
    } else if ((cp >= 0x139 && cp <= 0x148) ||
               (cp >= 0x179 && cp <= 0x17e) ||
               (cp >= 0x1af && cp <= 0x1b0) ||
               (cp >= 0x1b3 && cp <= 0x1b6) ||
               (cp >= 0x1cd && cp <= 0x1dc)) {
        cp = (cp - 1) | 1;
    } else {
        switch (cp) {
            case 0xff:   cp = 0x178; break;
            case 0x180:  cp = 0x243; break;
            case 0x188:  cp = 0x187; break;
            case 0x18c:  cp = 0x18b; break;
            case 0x192:  cp = 0x191; break;
            case 0x199:  cp = 0x198; break;
            case 0x19a:  cp = 0x23d; break;
            case 0x19e:  cp = 0x220; break;
            case 0x1a8:  cp = 0x1a7; break;
            case 0x1ad:  cp = 0x1ac; break;
            case 0x1b9:  cp = 0x1b8; break;
            case 0x1bd:  cp = 0x1bc; break;
            case 0x1bf:  cp = 0x1f7; break;
            case 0x1c6:  cp = 0x1c4; break;
            case 0x1c9:  cp = 0x1c7; break;
            case 0x1cc:  cp = 0x1ca; break;
            case 0x1dd:  cp = 0x18e; break;
            case 0x1f3:  cp = 0x1f1; break;
            case 0x1f5:  cp = 0x1f4; break;
            case 0x23c:  cp = 0x23b; break;
            case 0x242:  cp = 0x241; break;
            case 0x292:  cp = 0x1b7; break;
            case 0x371:  cp = 0x370; break;
            case 0x373:  cp = 0x372; break;
            case 0x377:  cp = 0x376; break;
            case 0x37b:  cp = 0x3fd; break;
            case 0x37c:  cp = 0x3fe; break;
            case 0x37d:  cp = 0x3ff; break;
            case 0x3ac:  cp = 0x386; break;
            case 0x3ad:  cp = 0x388; break;
            case 0x3ae:  cp = 0x389; break;
            case 0x3af:  cp = 0x38a; break;
            case 0x3cc:  cp = 0x38c; break;
            case 0x3cd:  cp = 0x38e; break;
            case 0x3ce:  cp = 0x38f; break;
            case 0x3d1:  cp = 0x398; break;
            case 0x3d7:  cp = 0x3cf; break;
            case 0x3f2:  cp = 0x3f9; break;
            case 0x3f3:  cp = 0x37f; break;
            case 0x3f8:  cp = 0x3f7; break;
            case 0x3fb:  cp = 0x3fa; break;
            default: break;
        }
    }
    
    return cp;
}