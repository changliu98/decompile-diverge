define MOD_ADLER 65521

uint64_t adler32_z(uint64_t adler, const unsigned char *buf, size_t len) {
    uint64_t sum2 = (adler >> 16) & 0xffff;
    adler &= 0xffff;

    // Single byte case
    if (len == 1) {
        adler += buf[0];
        if (adler >= MOD_ADLER) {
            adler -= MOD_ADLER;
        }
        sum2 += adler;
        if (sum2 >= MOD_ADLER) {
            sum2 -= MOD_ADLER;
        }
        return adler | (sum2 << 16);
    }

    // Null buffer case
    if (buf == NULL) {
        return 1;
    }

    // Initial length < 16 case
    if (len < 16) {
        while (len--) {
            adler += *buf++;
            sum2 += adler;
        }
        if (adler >= MOD_ADLER) {
            adler -= MOD_ADLER;
        }
        sum2 %= MOD_ADLER;
        return adler | (sum2 << 16);
    }

    // Main processing loop
    while (len >= 5552) {
        len -= 5552;
        int n = 347; // 347 * 16 = 5552
        do {
            // 16x unrolled loop
            for (int i = 0; i < 16; ++i) {
                adler += buf[i];
                sum2 += adler;
            }
            buf += 16;
        } while (--n);

        adler %= MOD_ADLER;
        sum2 %= MOD_ADLER;
    }

    // Process remaining chunks of 16 bytes
    while (len >= 16) {
        len -= 16;
        // 16x unrolled loop
        for (int i = 0; i < 16; ++i) {
            adler += buf[i];
            sum2 += adler;
        }
        buf += 16;
    }

    // Process remaining bytes
    while (len--) {
        adler += *buf++;
        sum2 += adler;
    }

    adler %= MOD_ADLER;
    sum2 %= MOD_ADLER;

    return adler | (sum2 << 16);
}