utf8_int32_t utf8uprcodepoint(utf8_int32_t cp)
{

    if ((cp >= 0x61 && cp <= 0x7A) ||
        (cp >= 0xE0 && cp <= 0xF6) ||
        (cp >= 0xF8 && cp <= 0xFE) ||
        (cp >= 0x3B1 && cp <= 0x3C1) ||
        (cp >= 0x3C3 && cp <= 0x3CB) ||
        (cp >= 0x430 && cp <= 0x44F) ||
        (cp >= 0x450 && cp <= 0x45F))
    {
        cp -= 0x20;
    }

    else if ((cp >= 0x100 && cp <= 0x12F) ||
             (cp >= 0x132 && cp <= 0x137) ||
             (cp >= 0x14A && cp <= 0x177) ||
             (cp >= 0x182 && cp <= 0x185) ||
             (cp >= 0x1A0 && cp <= 0x1A5) ||
             (cp >= 0x1DE && cp <= 0x1EF) ||
             (cp >= 0x1F8 && cp <= 0x21F) ||
             (cp >= 0x222 && cp <= 0x233) ||
             (cp >= 0x246 && cp <= 0x24F) ||
             (cp >= 0x3D8 && cp <= 0x3EF) ||
             (cp >= 0x460 && cp <= 0x481) ||
             (cp >= 0x48A && cp <= 0x4FF))
    {
        cp &= ~1;
    }

    else if (cp >= 0x450 && cp <= 0x45F)
    {
        cp -= 0x50;
    }

    else if ((cp >= 0x139 && cp <= 0x148) ||
             (cp >= 0x179 && cp <= 0x17E) ||
             (cp >= 0x1AF && cp <= 0x1B0) ||
             (cp >= 0x1B3 && cp <= 0x1B6) ||
             (cp >= 0x1CD && cp <= 0x1DC))
    {
        cp = (cp - 1) | 1;
    }

    else if (cp == 0x0FF)
    {
        cp = 0x178;
    }

    else if (cp == 0x180)
    {
        cp = 0x243;
    }

    else if (cp == 0x188)
    {
        cp = 0x187;
    }

    else if (cp == 0x18C)
    {
        cp = 0x18B;
    }

    else if (cp == 0x192)
    {
        cp = 0x191;
    }

    else if (cp == 0x199)
    {
        cp = 0x198;
    }

    else if (cp == 0x19A)
    {
        cp = 0x23D;
    }

    else if (cp == 0x19E)
    {
        cp = 0x220;
    }

    else if (cp == 0x1A8)
    {
        cp = 0x1A7;
    }

    else if (cp == 0x1AD)
    {
        cp = 0x1AC;
    }

    else if (cp == 0x1B9)
    {
        cp = 0x1B8;
    }

    else if (cp == 0x1BD)
    {
        cp = 0x1BC;
    }

    else if (cp == 0x1BF)
    {
        cp = 0x1F7;
    }

    else if (cp == 0x1C6)
    {
        cp = 0x1C4;
    }

    else if (cp == 0x1C9)
    {
        cp = 0x1C7;
    }

    else if (cp == 0x1CC)
    {
        cp = 0x1CA;
    }

    else if (cp == 0x1DD)
    {
        cp = 0x18E;
    }

    else if (cp == 0x1F3)
    {
        cp = 0x1F1;
    }

    else if (cp == 0x1F5)
    {
        cp = 0x1F4;
    }

    else if (cp == 0x23C)
    {
        cp = 0x23B;
    }

    else if (cp == 0x242)
    {
        cp = 0x241;
    }

    else if (cp == 0x292)
    {
        cp = 0x1B7;
    }

    else if (cp == 0x371)
    {
        cp = 0x370;
    }

    else if (cp == 0x373)
    {
        cp = 0x372;
    }

    else if (cp == 0x377)
    {
        cp = 0x376;
    }

    else if (cp == 0x37B)
    {
        cp = 0x3FD;
    }

    else if (cp == 0x37C)
    {
        cp = 0x3FE;
    }

    else if (cp == 0x37D)
    {
        cp = 0x3FF;
    }

    else if (cp == 0x3AC)
    {
        cp = 0x386;
    }

    else if (cp == 0x3AD)
    {
        cp = 0x388;
    }

    else if (cp == 0x3AE)
    {
        cp = 0x389;
    }

    else if (cp == 0x3AF)
    {
        cp = 0x38A;
    }

    else if (cp == 0x3CC)
    {
        cp = 0x38C;
    }

    else if (cp == 0x3CD)
    {
        cp = 0x38E;
    }

    else if (cp == 0x3CE)
    {
        cp = 0x38F;
    }

    else if (cp == 0x3D1)
    {
        cp = 0x398;
    }

    else if (cp == 0x3D7)
    {
        cp = 0x3CF;
    }

    else if (cp == 0x3F2)
    {
        cp = 0x3F9;
    }

    else if (cp == 0x3F3)
    {
        cp = 0x37F;
    }

    else if (cp == 0x3F8)
    {
        cp = 0x3F7;
    }

    else if (cp == 0x3FB)
    {
        cp = 0x3FA;
    }

    return cp;
}