void bn_sqr_comba8(uint64_t *r, const uint64_t *a) {
    uint64_t c0 = 0, c1 = 0, c2 = 0;
    uint64_t lo, hi;

    // Row 0
    lo = a[0] * a[0];
    hi = __umulh(a[0], a[0]);
    c0 += lo; c1 += hi; c2 += (c1 < hi);
    r[0] = c0; c0 = 0;

    // Row 1
    lo = a[1] * a[0];
    hi = __umulh(a[1], a[0]);
    c1 += lo; c2 += hi; c0 += (c2 < hi);
    c1 += lo; c2 += hi; c0 += (c2 < hi);
    r[1] = c1; c1 = 0;

    // Row 2
    lo = a[1] * a[1];
    hi = __umulh(a[1], a[1]);
    c2 += lo; c0 += hi; c1 += (c0 < hi);

    lo = a[2] * a[0];
    hi = __umulh(a[2], a[0]);
    c2 += lo; c0 += hi; c1 += (c0 < hi);
    c2 += lo; c0 += hi; c1 += (c0 < hi);
    r[2] = c2; c2 = 0;

    // Row 3
    lo = a[3] * a[0];
    hi = __umulh(a[3], a[0]);
    c0 += lo; c1 += hi; c2 += (c1 < hi);
    c0 += lo; c1 += hi; c2 += (c1 < hi);

    lo = a[2] * a[1];
    hi = __umulh(a[2], a[1]);
    c0 += lo; c1 += hi; c2 += (c1 < hi);
    c0 += lo; c1 += hi; c2 += (c1 < hi);
    r[3] = c0; c0 = 0;

    // Row 4
    lo = a[2] * a[2];
    hi = __umulh(a[2], a[2]);
    c1 += lo; c2 += hi; c0 += (c2 < hi);

    lo = a[3] * a[1];
    hi = __umulh(a[3], a[1]);
    c1 += lo; c2 += hi; c0 += (c2 < hi);
    c1 += lo; c2 += hi; c0 += (c2 < hi);

    lo = a[4] * a[0];
    hi = __umulh(a[4], a[0]);
    c1 += lo; c2 += hi; c0 += (c2 < hi);
    c1 += lo; c2 += hi; c0 += (c2 < hi);
    r[4] = c1; c1 = 0;

    // Row 5
    lo = a[5] * a[0];
    hi = __umulh(a[5], a[0]);
    c2 += lo; c0 += hi; c1 += (c0 < hi);
    c2 += lo; c0 += hi; c1 += (c0 < hi);

    lo = a[4] * a[1];
    hi = __umulh(a[4], a[1]);
    c2 += lo; c0 += hi; c1 += (c0 < hi);
    c2 += lo; c0 += hi; c1 += (c0 < hi);

    lo = a[3] * a[2];
    hi = __umulh(a[3], a[2]);
    c2 += lo; c0 += hi; c1 += (c0 < hi);
    c2 += lo; c0 += hi; c1 += (c0 < hi);
    r[5] = c2; c2 = 0;

    // Row 6
    lo = a[3] * a[3];
    hi = __umulh(a[3], a[3]);
    c0 += lo; c1 += hi; c2 += (c1 < hi);

    lo = a[4] * a[2];
    hi = __umulh(a[4], a[2]);
    c0 += lo; c1 += hi; c2 += (c1 < hi);
    c0 += lo; c1 += hi; c2 += (c1 < hi);

    lo = a[5] * a[1];
    hi = __umulh(a[5], a[1]);
    c0 += lo; c1 += hi; c2 += (c1 < hi);
    c0 += lo; c1 += hi; c2 += (c1 < hi);

    lo = a[6] * a[0];
    hi = __umulh(a[6], a[0]);
    c0 += lo; c1 += hi; c2 += (c1 < hi);
    c0 += lo; c1 += hi; c2 += (c1 < hi);
    r[6] = c0; c0 = 0;

    // Row 7
    lo = a[7] * a[0];
    hi = __umulh(a[7], a[0]);
    c1 += lo; c2 += hi; c0 += (c2 < hi);
    c1 += lo; c2 += hi; c0 += (c2 < hi);

    lo = a[6] * a[1];
    hi = __umulh(a[6], a[1]);
    c1 += lo; c2 += hi; c0 += (c2 < hi);
    c1 += lo; c2 += hi; c0 += (c2 < hi);

    lo = a[5] * a[2];
    hi = __umulh(a[5], a[2]);
    c1 += lo; c2 += hi; c0 += (c2 < hi);
    c1 += lo; c2 += hi; c0 += (c2 < hi);

    lo = a[4] * a[3];
    hi = __umulh(a[4], a[3]);
    c1 += lo; c2 += hi; c0 += (c2 < hi);
    c1 += lo; c2 += hi; c0 += (c2 < hi);
    r[7] = c1; c1 = 0;

    // Row 8
    lo = a[4] * a[4];
    hi = __umulh(a[4], a[4]);
    c2 += lo; c0 += hi; c1 += (c0 < hi);

    lo = a[5] * a[3];
    hi = __umulh(a[5], a[3]);
    c2 += lo; c0 += hi; c1 += (c0 < hi);
    c2 += lo; c0 += hi; c1 += (c0 < hi);

    lo = a[6] * a[2];
    hi = __umulh(a[6], a[2]);
    c2 += lo; c0 += hi; c1 += (c0 < hi);
    c2 += lo; c0 += hi; c1 += (c0 < hi);

    lo = a[7] * a[1];
    hi = __umulh(a[7], a[1]);
    c2 += lo; c0 += hi; c1 += (c0 < hi);
    c2 += lo; c0 += hi; c1 += (c0 < hi);
    r[8] = c2; c2 = 0;

    // Row 9
    lo = a[7] * a[2];
    hi = __umulh(a[7], a[2]);
    c0 += lo; c1 += hi; c2 += (c1 < hi);
    c0 += lo; c1 += hi; c2 += (c1 < hi);

    lo = a[6] * a[3];
    hi = __umulh(a[6], a[3]);
    c0 += lo; c1 += hi; c2 += (c1 < hi);
    c0 += lo; c1 += hi; c2 += (c1 < hi);

    lo = a[5] * a[4];
    hi = __umulh(a[5], a[4]);
    c0 += lo; c1 += hi; c2 += (c1 < hi);
    c0 += lo; c1 += hi; c2 += (c1 < hi);
    r[9] = c0; c0 = 0;

    // Row 10
    lo = a[5] * a[5];
    hi = __umulh(a[5], a[5]);
    c1 += lo; c2 += hi; c0 += (c2 < hi);

    lo = a[6] * a[4];
    hi = __umulh(a[6], a[4]);
    c1 += lo; c2 += hi; c0 += (c2 < hi);
    c1 += lo; c2 += hi; c0 += (c2 < hi);

    lo = a[7] * a[3];
    hi = __umulh(a[7], a[3]);
    c1 += lo; c2 += hi; c0 += (c2 < hi);
    c1 += lo; c2 += hi; c0 += (c2 < hi);
    r[10] = c1; c1 = 0;

    // Row 11
    lo = a[7] * a[4];
    hi = __umulh(a[7], a[4]);
    c2 += lo; c0 += hi; c1 += (c0 < hi);
    c2 += lo; c0 += hi; c1 += (c0 < hi);

    lo = a[6] * a[5];
    hi = __umulh(a[6], a[5]);
    c2 += lo; c0 += hi; c1 += (c0 < hi);
    c2 += lo; c0 += hi; c1 += (c0 < hi);
    r[11] = c2; c2 = 0;

    // Row 12
    lo = a[6] * a[6];
    hi = __umulh(a[6], a[6]);
    c0 += lo; c1 += hi; c2 += (c1 < hi);

    lo = a[7] * a[5];
    hi = __umulh(a[7], a[5]);
    c0 += lo; c1 += hi; c2 += (c1 < hi);
    c0 += lo; c1 += hi; c2 += (c1 < hi);
    r[12] = c0; c0 = 0;

    // Row 13
    lo = a[7] * a[6];
    hi = __umulh(a[7], a[6]);
    c1 += lo; c2 += hi; c0 += (c2 < hi);
    c1 += lo; c2 += hi; c0 += (c2 < hi);
    r[13] = c1; c1 = 0;

    // Row 14
    lo = a[7] * a[7];
    hi = __umulh(a[7], a[7]);
    c2 += lo; c0 += hi; c1 += (c0 < hi);
    r[14] = c2;

    // Row 15
    r[15] = c0;
}