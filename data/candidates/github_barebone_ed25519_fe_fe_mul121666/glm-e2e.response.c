void fe_mul121666(int32_t *out, const int32_t *in) {
    int64_t t0 = (int64_t)in[0] * 0x1db42;
    int64_t t1 = (int64_t)in[1] * 0x1db42;
    int64_t t2 = (int64_t)in[2] * 0x1db42;
    int64_t t3 = (int64_t)in[3] * 0x1db42;
    int64_t t4 = (int64_t)in[4] * 0x1db42;
    int64_t t5 = (int64_t)in[5] * 0x1db42;
    int64_t t6 = (int64_t)in[6] * 0x1db42;
    int64_t t7 = (int64_t)in[7] * 0x1db42;
    int64_t t8 = (int64_t)in[8] * 0x1db42;
    int64_t t9 = (int64_t)in[9] * 0x1db42;

    // First carry propagation pass
    int64_t c;

    // Carry from t9 to t0 (modular reduction by 2^255 - 19)
    c = (t9 + 0x1000000) >> 25;
    t0 += c * 19;
    t9 -= c << 25;

    // Carry from t1 to t2
    c = (t1 + 0x1000000) >> 25;
    t2 += c;
    t1 -= c << 25;

    // Carry from t3 to t4
    c = (t3 + 0x1000000) >> 25;
    t4 += c;
    t3 -= c << 25;

    // Carry from t5 to t6
    c = (t5 + 0x1000000) >> 25;
    t6 += c;
    t5 -= c << 25;

    // Carry from t7 to t8
    c = (t7 + 0x1000000) >> 25;
    t8 += c;
    t7 -= c << 25;

    // Second carry propagation pass
    // Carry from t0 to t1
    c = (t0 + 0x2000000) >> 26;
    t1 += c;
    t0 -= c << 26;

    // Carry from t2 to t3
    c = (t2 + 0x2000000) >> 26;
    t3 += c;
    t2 -= c << 26;

    // Carry from t4 to t5
    c = (t4 + 0x2000000) >> 26;
    t5 += c;
    t4 -= c << 26;

    // Carry from t6 to t7
    c = (t6 + 0x2000000) >> 26;
    t7 += c;
    t6 -= c << 26;

    // Carry from t8 to t9
    c = (t8 + 0x2000000) >> 26;
    t9 += c;
    t8 -= c << 26;

    // Store the lower 32 bits of each 64-bit limb back to the output array
    out[0] = (int32_t)t0;
    out[1] = (int32_t)t1;
    out[2] = (int32_t)t2;
    out[3] = (int32_t)t3;
    out[4] = (int32_t)t4;
    out[5] = (int32_t)t5;
    out[6] = (int32_t)t6;
    out[7] = (int32_t)t7;
    out[8] = (int32_t)t8;
    out[9] = (int32_t)t9;
}