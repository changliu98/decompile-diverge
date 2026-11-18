utf8_int32_t utf8lwrcodepoint(utf8_int32_t cp)
{

    if ((cp >= 0x41 && cp <= 0x5A) || (cp >= 0xC0 && cp <= 0xD6) || (cp >= 0xD8 && cp <= 0xDE) || (cp >= 0x391 && cp <= 0x3A1) || (cp >= 0x3A3 && cp <= 0x3AB) || (cp >= 0x410 && cp <= 0x42F)) {
        cp += 0x20;
    } else if (cp >= 0x400 && cp <= 0x40F) {
        cp += 0x50;
    } else if ((cp >= 0x100 && cp <= 0x12F) || (cp >= 0x132 && cp <= 0x137) || (cp >= 0x14A && cp <= 0x177) || (cp >= 0x182 && cp <= 0x185) || (cp >= 0x1A0 && cp <= 0x1A5) || (cp >= 0x1DE && cp <= 0x1EF) || (cp >= 0x1F8 && cp <= 0x21F) || (cp >= 0x222 && cp <= 0x233) || (cp >= 0x246 && cp <= 0x24F) || (cp >= 0x3D8 && cp <= 0x3EF) || (cp >= 0x460 && cp <= 0x481) || (cp >= 0x48A && cp <= 0x4FF)) {
        cp |= 0x1;
    } else if ((cp >= 0x139 && cp <= 0x148) || (cp >= 0x179 && cp <= 0x17E) || (cp >= 0x1AF && cp <= 0x1B0) || (cp >= 0x1B3 && cp <= 0x1B6) || (cp >= 0x1CD && cp <= 0x1DC)) {
        cp = (cp + 1) & ~0x1;
    } else if (cp == 0x178) {
        cp = 0xFF;
    } else if (cp == 0x187) {
        cp = 0x188;
    } else if (cp == 0x18B) {
        cp = 0x18C;
    } else if (cp == 0x18E) {
        cp = 0x1DD;
    } else if (cp == 0x191) {
        cp = 0x192;
    } else if (cp == 0x198) {
        cp = 0x199;
    } else if (cp == 0x1A7) {
        cp = 0x1A8;
    } else if (cp == 0x1AC) {
        cp = 0x1AD;
    } else if (cp == 0x1B7) {
        cp = 0x292;
    } else if (cp == 0x1B8) {
        cp = 0x1B9;
    } else if (cp == 0x1BC) {
        cp = 0x1BD;
    } else if (cp == 0x1C4) {
        cp = 0x1C6;
    } else if (cp == 0x1C7) {
        cp = 0x1C9;
    } else if (cp == 0x1CA) {
        cp = 0x1CC;
    } else if (cp == 0x1F1) {
        cp = 0x1F3;
    } else if (cp == 0x1F2) {
        cp = 0x1F5;
    } else if (cp == 0x1F7) {
        cp = 0x1BF;
    } else if (cp == 0x220) {
        cp = 0x19E;
    } else if (cp == 0x23B) {
        cp = 0x23C;
    } else if (cp == 0x23D) {
        cp = 0x19A;
    } else if (cp == 0x241) {
        cp = 0x242;
    } else if (cp == 0x243) {
        cp = 0x180;
    } else if (cp == 0x370) {
        cp = 0x371;
    } else if (cp == 0x372) {
        cp = 0x373;
    } else if (cp == 0x376) {
        cp = 0x377;
    } else if (cp == 0x37F) {
        cp = 0x3F3;
    } else if (cp == 0x386) {
        cp = 0x3AC;
    } else if (cp == 0x388) {
        cp = 0x3AD;
    } else if (cp == 0x389) {
        cp = 0x3AE;
    } else if (cp == 0x38A) {
        cp = 0x3AF;
    } else if (cp == 0x38C) {
        cp = 0x3CC;
    } else if (cp == 0x38E) {
        cp = 0x3CD;
    } else if (cp == 0x38F) {
        cp = 0x3CE;
    } else if (cp == 0x3CF) {
        cp = 0x3D7;
    } else if (cp == 0x3F4) {
        cp = 0x3B8;
    } else if (cp == 0x3F7) {
        cp = 0x3F8;
    } else if (cp == 0x3F9) {
        cp = 0x3F2;
    } else if (cp == 0x3FA) {
        cp = 0x3FB;
    } else if (cp == 0x3FD) {
        cp = 0x37B;
    } else if (cp == 0x3FE) {
        cp = 0x37C;
    } else if (cp == 0x3FF) {
        cp = 0x37D;
    }

    return cp;
}