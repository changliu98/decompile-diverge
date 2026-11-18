void bn_mul_comba4(uint32_t *r, uint32_t *a, uint32_t *b) {
    uint32_t c0 = 0, c1 = 0, c2 = 0;
    uint32_t a0, a1, a2, a3;
    uint32_t b0, b1, b2, b3;
    uint32_t lo, hi;

    // Round 1: a0*b0
    a0 = a[0] & 0xffff;
    a1 = a[0] >> 16;
    b0 = b[0] & 0xffff;
    b1 = b[0] >> 16;

    lo = a0 * b0;
    hi = a1 * b1;
    {
        uint32_t mid = (a0 * b1) + (a1 * b0);
        hi += (mid >> 16) + (lo > (lo + (mid << 16)) ? 1 : 0);
        lo = lo + (mid << 16);
    }
    c0 = lo;
    c1 = hi;
    c2 = 0;
    r[0] = c0;

    // Round 2: a0*b1 + a1*b0
    a0 = a[0] & 0xffff;
    a1 = a[0] >> 16;
    b0 = b[1] & 0xffff;
    b1 = b[1] >> 16;

    lo = a0 * b0;
    hi = a1 * b1;
    {
        uint32_t mid = (a0 * b1) + (a1 * b0);
        hi += (mid >> 16) + (lo > (lo + (mid << 16)) ? 1 : 0);
        lo = lo + (mid << 16);
    }
    c1 += lo;
    if (c1 < lo) c2++;
    c2 += hi;
    if (c2 < hi) c0 = 1; // c0 was 0, effectively c0 = 1
    else c0 = 0;

    a0 = a[1] & 0xffff;
    a1 = a[1] >> 16;
    b0 = b[0] & 0xffff;
    b1 = b[0] >> 16;

    lo = a0 * b0;
    hi = a1 * b1;
    {
        uint32_t mid = (a0 * b1) + (a1 * b0);
        hi += (mid >> 16) + (lo > (lo + (mid << 16)) ? 1 : 0);
        lo = lo + (mid << 16);
    }
    c1 += lo;
    if (c1 < lo) c2++;
    c2 += hi;
    if (c2 < hi) c0++;
    r[1] = c1;
    c1 = 0;

    // Round 3: a0*b2 + a1*b1 + a2*b0
    a0 = a[2] & 0xffff;
    a1 = a[2] >> 16;
    b0 = b[0] & 0xffff;
    b1 = b[0] >> 16;

    lo = a0 * b0;
    hi = a1 * b1;
    {
        uint32_t mid = (a0 * b1) + (a1 * b0);
        hi += (mid >> 16) + (lo > (lo + (mid << 16)) ? 1 : 0);
        lo = lo + (mid << 16);
    }
    c2 += lo;
    if (c2 < lo) c0++;
    c0 += hi;
    if (c0 < hi) c1++;

    a0 = a[1] & 0xffff;
    a1 = a[1] >> 16;
    b0 = b[1] & 0xffff;
    b1 = b[1] >> 16;

    lo = a0 * b0;
    hi = a1 * b1;
    {
        uint32_t mid = (a0 * b1) + (a1 * b0);
        hi += (mid >> 16) + (lo > (lo + (mid << 16)) ? 1 : 0);
        lo = lo + (mid << 16);
    }
    c2 += lo;
    if (c2 < lo) c0++;
    c0 += hi;
    if (c0 < hi) c1++;

    a0 = a[0] & 0xffff;
    a1 = a[0] >> 16;
    b0 = b[2] & 0xffff;
    b1 = b[2] >> 16;

    lo = a0 * b0;
    hi = a1 * b1;
    {
        uint32_t mid = (a0 * b1) + (a1 * b0);
        hi += (mid >> 16) + (lo > (lo + (mid << 16)) ? 1 : 0);
        lo = lo + (mid << 16);
    }
    c2 += lo;
    if (c2 < lo) c0++;
    c0 += hi;
    if (c0 < hi) c1++;
    r[2] = c2;
    c2 = 0;

    // Round 4: a0*b3 + a1*b2 + a2*b1 + a3*b0
    a0 = a[0] & 0xffff;
    a1 = a[0] >> 16;
    b0 = b[3] & 0xffff;
    b1 = b[3] >> 16;

    lo = a0 * b0;
    hi = a1 * b1;
    {
        uint32_t mid = (a0 * b1) + (a1 * b0);
        hi += (mid >> 16) + (lo > (lo + (mid << 16)) ? 1 : 0);
        lo = lo + (mid << 16);
    }
    c0 += lo;
    if (c0 < lo) c1++;
    c1 += hi;
    if (c1 < hi) c2++;

    a0 = a[1] & 0xffff;
    a1 = a[1] >> 16;
    b0 = b[2] & 0xffff;
    b1 = b[2] >> 16;

    lo = a0 * b0;
    hi = a1 * b1;
    {
        uint32_t mid = (a0 * b1) + (a1 * b0);
        hi += (mid >> 16) + (lo > (lo + (mid << 16)) ? 1 : 0);
        lo = lo + (mid << 16);
    }
    c0 += lo;
    if (c0 < lo) c1++;
    c1 += hi;
    if (c1 < hi) c2++;

    a0 = a[2] & 0xffff;
    a1 = a[2] >> 16;
    b0 = b[1] & 0xffff;
    b1 = b[1] >> 16;

    lo = a0 * b0;
    hi = a1 * b1;
    {
        uint32_t mid = (a0 * b1) + (a1 * b0);
        hi += (mid >> 16) + (lo > (lo + (mid << 16)) ? 1 : 0);
        lo = lo + (mid << 16);
    }
    c0 += lo;
    if (c0 < lo) c1++;
    c1 += hi;
    if (c1 < hi) c2++;

    a0 = a[3] & 0xffff;
    a1 = a[3] >> 16;
    b0 = b[0] & 0xffff;
    b1 = b[0] >> 16;

    lo = a0 * b0;
    hi = a1 * b1;
    {
        uint32_t mid = (a0 * b1) + (a1 * b0);
        hi += (mid >> 16) + (lo > (lo + (mid << 16)) ? 1 : 0);
        lo = lo + (mid << 16);
    }
    c0 += lo;
    if (c0 < lo) c1++;
    c1 += hi;
    if (c1 < hi) c2++;
    r[3] = c0;
    c0 = 0;

    // Round 5: a1*b3 + a2*b2 + a3*b1
    a0 = a[1] & 0xffff;
    a1 = a[1] >> 16;
    b0 = b[3] & 0xffff;
    b1 = b[3] >> 16;

    lo = a0 * b0;
    hi = a1 * b1;
    {
        uint32_t mid = (a0 * b1) + (a1 * b0);
        hi += (mid >> 16) + (lo > (lo + (mid << 16)) ? 1 : 0);
        lo = lo + (mid << 16);
    }
    c1 += lo;
    if (c1 < lo) c2++;
    c2 += hi;
    if (c2 < hi) c0++;

    a0 = a[2] & 0xffff;
    a1 = a[2] >> 16;
    b0 = b[2] & 0xffff;
    b1 = b[2] >> 16;

    lo = a0 * b0;
    hi = a1 * b1;
    {
        uint32_t mid = (a0 * b1) + (a1 * b0);
        hi += (mid >> 16) + (lo > (lo + (mid << 16)) ? 1 : 0);
        lo = lo + (mid << 16);
    }
    c1 += lo;
    if (c1 < lo) c2++;
    c2 += hi;
    if (c2 < hi) c0++;

    a0 = a[3] & 0xffff;
    a1 = a[3] >> 16;
    b0 = b[1] & 0xffff;
    b1 = b[1] >> 16;

    lo = a0 * b0;
    hi = a1 * b1;
    {
        uint32_t mid = (a0 * b1) + (a1 * b0);
        hi += (mid >> 16) + (lo > (lo + (mid << 16)) ? 1 : 0);
        lo = lo + (mid << 16);
    }
    c1 += lo;
    if (c1 < lo) c2++;
    c2 += hi;
    if (c2 < hi) c0++;
    r[4] = c1;
    c1 = 0;

    // Round 6: a2*b3 + a3*b2
    a0 = a[2] & 0xffff;
    a1 = a[2] >> 16;
    b0 = b[3] & 0xffff;
    b1 = b[3] >> 16;

    lo = a0 * b0;
    hi = a1 * b1;
    {
        uint32_t mid = (a0 * b1) + (a1 * b0);
        hi += (mid >> 16) + (lo > (lo + (mid << 16)) ? 1 : 0);
        lo = lo + (mid << 16);
    }
    c2 += lo;
    if (c2 < lo) c0++;
    c0 += hi;
    if (c0 < hi) c1++;

    a0 = a[3] & 0xffff;
    a1 = a[3] >> 16;
    b0 = b[2] & 0xffff;
    b1 = b[2] >> 16;

    lo = a0 * b0;
    hi = a1 * b1;
    {
        uint32_t mid = (a0 * b1) + (a1 * b0);
        hi += (mid >> 16) + (lo > (lo + (mid << 16)) ? 1 : 0);
        lo = lo + (mid << 16);
    }
    c2 += lo;
    if (c2 < lo) c0++;
    c0 += hi;
    if (c0 < hi) c1++;
    r[5] = c2;

    // Round 7: a3*b3
    a0 = a[3] & 0xffff;
    a1 = a[3] >> 16;
    b0 = b[3] & 0xffff;
    b1 = b[3] >> 16;

    lo = a0 * b0;
    hi = a1 * b1;
    {
        uint32_t mid = (a0 * b1) + (a1 * b0);
        hi += (mid >> 16) + (lo > (lo + (mid << 16)) ? 1 : 0);
        lo = lo + (mid << 16);
    }
    c0 += lo;
    if (c0 < lo) c1++;
    c1 += hi;
    if (c1 < hi) c2++; // Overflow ignored as it goes beyond 8 words

    r[6] = c0;
    r[7] = c1;
}