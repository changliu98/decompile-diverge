void SdnToJulian(int64_t sdn, int *year, int *month, int *day) {
    int64_t jdn;
    int64_t z;
    int64_t y;
    int64_t d;
    int64_t m;

    // Check if sdn is out of valid bounds
    if (sdn <= 0 || 
        (sdn > 0x1fffffffffff82adLL && sdn < 0xe000000000000000LL)) {
        *year = 0;
        *month = 0;
        *day = 0;
        return;
    }

    jdn = (sdn << 2) + 0x1f54b;
    y = jdn / 1461;

    // Check if the calculated year fits in a 32-bit integer
    if (y > 0x7fffffffLL || y < (int64_t)0xffffffff80000000LL) {
        *year = 0;
        *month = 0;
        *day = 0;
        return;
    }

    z = (jdn % 1461) / 4 + 1;
    jdn = z * 5 - 3;
    m = jdn / 153;
    d = (jdn % 153) / 5 + 1;

    if (m < 10) {
        m += 3;
    } else {
        y += 1;
        m -= 9;
    }

    y -= 0x12c0; // Subtract 4800

    if (y <= 0) {
        y -= 1; // Adjust for BC years (no year 0)
    }

    *year = (int)y;
    *month = (int)m;
    *day = (int)d;
}