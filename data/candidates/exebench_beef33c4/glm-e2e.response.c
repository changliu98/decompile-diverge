void bn_mul_comba4(uint64_t *r, const uint64_t *a, const uint64_t *b) {
    uint64_t c0 = 0, c1 = 0, c2 = 0;
    uint64_t lo, hi;

    // Column 0: a[0] * b[0]
    lo = a[0] * b[0];
    hi = (a[0] * b[0]) >> 32; // Emulated via mulq
    c0 += lo; c1 += (c0 < lo) + hi; c2 += (c1 < hi);
    r[0] = c0;
    c0 = 0;

    // Column 1: a[0] * b[1] + a[1] * b[0]
    lo = a[0] * b[1];
    hi = (a[0] * b[1]) >> 32;
    c1 += lo; c2 += (c1 < lo) + hi; c0 += (c2 < hi);
    
    lo = a[1] * b[0];
    hi = (a[1] * b[0]) >> 32;
    c1 += lo; c2 += (c1 < lo) + hi; c0 += (c2 < hi);
    r[1] = c1;
    c1 = 0;

    // Column 2: a[0] * b[2] + a[1] * b[1] + a[2] * b[0]
    lo = a[0] * b[2];
    hi = (a[0] * b[2]) >> 32;
    c2 += lo; c0 += (c2 < lo) + hi; c1 += (c0 < hi);
    
    lo = a[1] * b[1];
    hi = (a[1] * b[1]) >> 32;
    c2 += lo; c0 += (c2 < lo) + hi; c1 += (c0 < hi);
    
    lo = a[2] * b[0];
    hi = (a[2] * b[0]) >> 32;
    c2 += lo; c0 += (c2 < lo) + hi; c1 += (c0 < hi);
    r[2] = c2;
    c2 = 0;

    // Column 3: a[0] * b[3] + a[1] * b[2] + a[2] * b[1] + a[3] * b[0]
    lo = a[0] * b[3];
    hi = (a[0] * b[3]) >> 32;
    c0 += lo; c1 += (c0 < lo) + hi; c2 += (c1 < hi);
    
    lo = a[1] * b[2];
    hi = (a[1] * b[2]) >> 32;
    c0 += lo; c1 += (c0 < lo) + hi; c2 += (c1 < hi);
    
    lo = a[2] * b[1];
    hi = (a[2] * b[1]) >> 32;
    c0 += lo; c1 += (c0 < lo) + hi; c2 += (c1 < hi);
    
    lo = a[3] * b[0];
    hi = (a[3] * b[0]) >> 32;
    c0 += lo; c1 += (c0 < lo) + hi; c2 += (c1 < hi);
    r[3] = c0;
    c0 = 0;

    // Column 4: a[1] * b[3] + a[2] * b[2] + a[3] * b[1]
    lo = a[1] * b[3];
    hi = (a[1] * b[3]) >> 32;
    c1 += lo; c2 += (c1 < lo) + hi; c0 += (c2 < hi);
    
    lo = a[2] * b[2];
    hi = (a[2] * b[2]) >> 32;
    c1 += lo; c2 += (c1 < lo) + hi; c0 += (c2 < hi);
    
    lo = a[3] * b[1];
    hi = (a[3] * b[1]) >> 32;
    c1 += lo; c2 += (c1 < lo) + hi; c0 += (c2 < hi);
    r[4] = c1;
    c1 = 0;

    // Column 5: a[2] * b[3] + a[3] * b[2]
    lo = a[2] * b[3];
    hi = (a[2] * b[3]) >> 32;
    c2 += lo; c0 += (c2 < lo) + hi; c1 += (c0 < hi);
    
    lo = a[3] * b[2];
    hi = (a[3] * b[2]) >> 32;
    c2 += lo; c0 += (c2 < lo) + hi; c1 += (c0 < hi);
    r[5] = c2;
    c2 = 0;

    // Column 6: a[3] * b[3]
    lo = a[3] * b[3];
    hi = (a[3] * b[3]) >> 32;
    c0 += lo; c1 += (c0 < lo) + hi; c2 += (c1 < hi);
    r[6] = c0;
    r[7] = c1;
}