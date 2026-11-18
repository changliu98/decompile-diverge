void bn_sqr_comba4(uint64_t *r, const uint64_t *a) {
    uint64_t c0 = 0, c1 = 0, c2 = 0;
    uint64_t t_lo, t_hi;

    // Row 0: r[0] = a[0]^2
    t_lo = a[0] * a[0];
    t_hi = __umulh(a[0], a[0]);
    c0 += t_lo;
    c1 += t_hi + (c0 < t_lo);
    c2 += (c1 < t_hi) || ((c1 == t_hi) && (c0 < t_lo));
    r[0] = c0;
    c0 = 0;

    // Row 1: r[1] = 2 * a[0] * a[1]
    t_lo = a[1] * a[0];
    t_hi = __umulh(a[1], a[0]);
    c1 += t_lo;
    c2 += t_hi + (c1 < t_lo);
    c0 += (c2 < t_hi) || ((c2 == t_hi) && (c1 < t_lo));
    
    c1 += t_lo;
    c2 += t_hi + (c1 < t_lo);
    c0 += (c2 < t_hi) || ((c2 == t_hi) && (c1 < t_lo));
    r[1] = c1;
    c1 = 0;

    // Row 2: r[2] = a[1]^2 + 2 * a[0] * a[2]
    t_lo = a[1] * a[1];
    t_hi = __umulh(a[1], a[1]);
    c2 += t_lo;
    c0 += t_hi + (c2 < t_lo);
    c1 += (c0 < t_hi) || ((c0 == t_hi) && (c2 < t_lo));

    t_lo = a[2] * a[0];
    t_hi = __umulh(a[2], a[0]);
    c2 += t_lo;
    c0 += t_hi + (c2 < t_lo);
    c1 += (c0 < t_hi) || ((c0 == t_hi) && (c2 < t_lo));
    
    c2 += t_lo;
    c0 += t_hi + (c2 < t_lo);
    c1 += (c0 < t_hi) || ((c0 == t_hi) && (c2 < t_lo));
    r[2] = c2;
    c2 = 0;

    // Row 3: r[3] = 2 * (a[0] * a[3] + a[1] * a[2])
    t_lo = a[3] * a[0];
    t_hi = __umulh(a[3], a[0]);
    c0 += t_lo;
    c1 += t_hi + (c0 < t_lo);
    c2 += (c1 < t_hi) || ((c1 == t_hi) && (c0 < t_lo));
    
    c0 += t_lo;
    c1 += t_hi + (c0 < t_lo);
    c2 += (c1 < t_hi) || ((c1 == t_hi) && (c0 < t_lo));

    t_lo = a[2] * a[1];
    t_hi = __umulh(a[2], a[1]);
    c0 += t_lo;
    c1 += t_hi + (c0 < t_lo);
    c2 += (c1 < t_hi) || ((c1 == t_hi) && (c0 < t_lo));
    
    c0 += t_lo;
    c1 += t_hi + (c0 < t_lo);
    c2 += (c1 < t_hi) || ((c1 == t_hi) && (c0 < t_lo));
    r[3] = c0;
    c0 = 0;

    // Row 4: r[4] = a[2]^2 + 2 * a[1] * a[3]
    t_lo = a[2] * a[2];
    t_hi = __umulh(a[2], a[2]);
    c1 += t_lo;
    c2 += t_hi + (c1 < t_lo);
    c0 += (c2 < t_hi) || ((c2 == t_hi) && (c1 < t_lo));

    t_lo = a[3] * a[1];
    t_hi = __umulh(a[3], a[1]);
    c1 += t_lo;
    c2 += t_hi + (c1 < t_lo);
    c0 += (c2 < t_hi) || ((c2 == t_hi) && (c1 < t_lo));
    
    c1 += t_lo;
    c2 += t_hi + (c1 < t_lo);
    c0 += (c2 < t_hi) || ((c2 == t_hi) && (c1 < t_lo));
    r[4] = c1;
    c1 = 0;

    // Row 5: r[5] = 2 * a[2] * a[3]
    t_lo = a[3] * a[2];
    t_hi = __umulh(a[3], a[2]);
    c2 += t_lo;
    c0 += t_hi + (c2 < t_lo);
    c1 += (c0 < t_hi) || ((c0 == t_hi) && (c2 < t_lo));
    
    c2 += t_lo;
    c0 += t_hi + (c2 < t_lo);
    c1 += (c0 < t_hi) || ((c0 == t_hi) && (c2 < t_lo));
    r[5] = c2;
    c2 = 0;

    // Row 6: r[6] = a[3]^2
    t_lo = a[3] * a[3];
    t_hi = __umulh(a[3], a[3]);
    c0 += t_lo;
    c1 += t_hi + (c0 < t_lo);
    c2 += (c1 < t_hi) || ((c1 == t_hi) && (c0 < t_lo));
    r[6] = c0;
    r[7] = c1;
}