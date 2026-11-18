void bn_mul_comba8(uint64_t *out, const uint64_t *a, const uint64_t *b) {
    uint64_t c0 = 0, c1 = 0, c2 = 0;

    // Helper macro-like inline function for 64x64 -> 128 bit multiplication
    // It splits the 64-bit inputs into two 32-bit halves, multiplies them,
    // and accumulates the results into c0, c1, c2.
    #define mul_add_c(a_val, b_val) do { \
        uint64_t a_lo = (a_val) & 0xFFFFFFFFULL; \
        uint64_t a_hi = (a_val) >> 32; \
        uint64_t b_lo = (b_val) & 0xFFFFFFFFULL; \
        uint64_t b_hi = (b_val) >> 32; \
        uint64_t ll = a_lo * b_lo; \
        uint64_t hl = a_hi * b_lo; \
        uint64_t lh = a_lo * b_hi; \
        uint64_t hh = a_hi * b_hi; \
        uint64_t tmp = ll + lh; \
        if (tmp < ll) hh += 0x100000000ULL; \
        hh += tmp >> 32; \
        ll = (tmp << 32) & 0xFFFFFFFFULL; \
        tmp = hl + ll; \
        if (tmp < ll) hh += 1; \
        c0 += tmp & 0xFFFFFFFFULL; \
        if (c0 < (tmp & 0xFFFFFFFFULL)) c1++; \
        c1 += hh & 0xFFFFFFFFULL; \
        if (c1 < (hh & 0xFFFFFFFFULL)) c2++; \
    } while (0)

    // Column 0
    mul_add_c(a[0], b[0]);
    out[0] = c0; c0 = 0;

    // Column 1
    mul_add_c(a[0], b[1]);
    mul_add_c(a[1], b[0]);
    out[1] = c0; c0 = 0;

    // Column 2
    mul_add_c(a[0], b[2]);
    mul_add_c(a[1], b[1]);
    mul_add_c(a[2], b[0]);
    out[2] = c0; c0 = 0;

    // Column 3
    mul_add_c(a[0], b[3]);
    mul_add_c(a[1], b[2]);
    mul_add_c(a[2], b[1]);
    mul_add_c(a[3], b[0]);
    out[3] = c0; c0 = 0;

    // Column 4
    mul_add_c(a[0], b[4]);
    mul_add_c(a[1], b[3]);
    mul_add_c(a[2], b[2]);
    mul_add_c(a[3], b[1]);
    mul_add_c(a[4], b[0]);
    out[4] = c0; c0 = 0;

    // Column 5
    mul_add_c(a[0], b[5]);
    mul_add_c(a[1], b[4]);
    mul_add_c(a[2], b[3]);
    mul_add_c(a[3], b[2]);
    mul_add_c(a[4], b[1]);
    mul_add_c(a[5], b[0]);
    out[5] = c0; c0 = 0;

    // Column 6
    mul_add_c(a[0], b[6]);
    mul_add_c(a[1], b[5]);
    mul_add_c(a[2], b[4]);
    mul_add_c(a[3], b[3]);
    mul_add_c(a[4], b[2]);
    mul_add_c(a[5], b[1]);
    mul_add_c(a[6], b[0]);
    out[6] = c0; c0 = 0;

    // Column 7
    mul_add_c(a[0], b[7]);
    mul_add_c(a[1], b[6]);
    mul_add_c(a[2], b[5]);
    mul_add_c(a[3], b[4]);
    mul_add_c(a[4], b[3]);
    mul_add_c(a[5], b[2]);
    mul_add_c(a[6], b[1]);
    mul_add_c(a[7], b[0]);
    out[7] = c0; c0 = 0;

    // Column 8
    mul_add_c(a[1], b[7]);
    mul_add_c(a[2], b[6]);
    mul_add_c(a[3], b[5]);
    mul_add_c(a[4], b[4]);
    mul_add_c(a[5], b[3]);
    mul_add_c(a[6], b[2]);
    mul_add_c(a[7], b[1]);
    out[8] = c0; c0 = 0;

    // Column 9
    mul_add_c(a[2], b[7]);
    mul_add_c(a[3], b[6]);
    mul_add_c(a[4], b[5]);
    mul_add_c(a[5], b[4]);
    mul_add_c(a[6], b[3]);
    mul_add_c(a[7], b[2]);
    out[9] = c0; c0 = 0;

    // Column 10
    mul_add_c(a[3], b[7]);
    mul_add_c(a[4], b[6]);
    mul_add_c(a[5], b[5]);
    mul_add_c(a[6], b[4]);
    mul_add_c(a[7], b[3]);
    out[10] = c0; c0 = 0;

    // Column 11
    mul_add_c(a[4], b[7]);
    mul_add_c(a[5], b[6]);
    mul_add_c(a[6], b[5]);
    mul_add_c(a[7], b[4]);
    out[11] = c0; c0 = 0;

    // Column 12
    mul_add_c(a[5], b[7]);
    mul_add_c(a[6], b[6]);
    mul_add_c(a[7], b[5]);
    out[12] = c0; c0 = 0;

    // Column 13
    mul_add_c(a[6], b[7]);
    mul_add_c(a[7], b[6]);
    out[13] = c0; c0 = 0;

    // Column 14
    mul_add_c(a[7], b[7]);
    out[14] = c0;
    out[15] = c1;
}