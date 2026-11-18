void cftf081(float *a) {
    // 0xe14(%rip) typically points to a constant like 0.70710678f (1/sqrt(2))
    float wn = 0.70710678f; 

    // Stage 1: 2-point FFTs (Butterflies)
    float a0p4_0 = a[0] + a[8];
    float a0p4_1 = a[1] + a[9];
    float a0m4_0 = a[0] - a[8];
    float a0m4_1 = a[1] - a[9];

    float a2p6_0 = a[4] + a[12];
    float a2p6_1 = a[5] + a[13];
    float a2m6_0 = a[4] - a[12];
    float a2m6_1 = a[5] - a[13];

    // Stage 2: 4-point FFTs
    float y0_0 = a0p4_0 + a2p6_0;
    float y0_1 = a0p4_1 + a2p6_1;
    float y4_0 = a0p4_0 - a2p6_0;
    float y4_1 = a0p4_1 - a2p6_1;

    float y2_0 = a0m4_0 - a2m6_1;
    float y2_1 = a0m4_1 + a2m6_0;
    float y6_0 = a0m4_0 + a2m6_1;
    float y6_1 = a0m4_1 - a2m6_0;

    float a1p5_0 = a[2] + a[10];
    float a1p5_1 = a[3] + a[11];
    float a1m5_0 = a[2] - a[10];
    float a1m5_1 = a[3] - a[11];

    float a3p7_0 = a[6] + a[14];
    float a3p7_1 = a[7] + a[15];
    float a3m7_0 = a[6] - a[14];
    float a3m7_1 = a[7] - a[15];

    float y1_0 = a1p5_0 + a3p7_0;
    float y1_1 = a1p5_1 + a3p7_1;
    float y5_0 = a1p5_0 - a3p7_0;
    float y5_1 = a1p5_1 - a3p7_1;

    float x2_0 = a1m5_0 - a3m7_1;
    float x2_1 = a1m5_1 + a3m7_0;
    float x6_0 = a1m5_0 + a3m7_1;
    float x6_1 = a1m5_1 - a3m7_0;

    // Stage 3: 8-point FFTs (Twiddle factor multiplications)
    float t2_0 = wn * (x2_0 - x2_1);
    float t2_1 = wn * (x2_0 + x2_1);
    float t6_0 = wn * (x6_0 - x6_1);
    float t6_1 = wn * (x6_0 + x6_1);

    // Final outputs mapped back to the array
    a[8]  = y2_0 + t2_0;
    a[9]  = y2_1 + t2_1;
    a[10] = y2_0 - t2_0;
    a[11] = y2_1 - t2_1;

    a[12] = y6_0 - t6_1;
    a[13] = y6_1 + t6_0;
    a[14] = y6_0 + t6_1;
    a[15] = y6_1 - t6_0;

    a[0]  = y0_0 + y1_0;
    a[1]  = y0_1 + y1_1;
    a[2]  = y0_0 - y1_0;
    a[3]  = y0_1 - y1_1;

    a[4]  = y4_0 - y5_1;
    a[5]  = y4_1 + y5_0;
    a[6]  = y4_0 + y5_1;
    a[7]  = y4_1 - y5_0;
}