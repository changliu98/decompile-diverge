void crecip(limb *out, limb *z)
{
    limb temp1[10];
    limb temp0[10];
    limb z_pow_100[10];
    limb z_pow_50[10];
    limb z_pow_20[10];
    limb z_pow_10[10];
    limb z_pow_5[10];
    limb z_pow_11[10];
    limb z_pow_9[10];
    limb z_pow_2[10];
    int loop_idx;

    // Compute z^2
    fsquare(z_pow_2, z);
    // Compute z^4
    fsquare(temp1, z_pow_2);
    // Compute z^8
    fsquare(temp0, temp1);
    // Compute z^9 = z^8 * z
    fmul(z_pow_9, temp0, z);
    // Compute z^11 = z^9 * z^2
    fmul(z_pow_11, z_pow_9, z_pow_2);
    // Compute z^22 = z^11^2
    fsquare(temp0, z_pow_11);
    // Compute z^31 = z^22 * z^9
    fmul(z_pow_5, temp0, z_pow_9);
    
    // Compute z^62 = z^31^2
    fsquare(temp0, z_pow_5);
    // Compute z^124 = z^62^2
    fsquare(temp1, temp0);
    // Compute z^248 = z^124^2
    fsquare(temp0, temp1);
    // Compute z^496 = z^248^2
    fsquare(temp1, temp0);
    // Compute z^992 = z^496^2
    fsquare(temp0, temp1);
    // Compute z^1023 = z^992 * z^31
    fmul(z_pow_10, temp0, z_pow_5);
    
    // Compute z^2046 = z^1023^2
    fsquare(temp0, z_pow_10);
    // Compute z^4092 = z^2046^2
    fsquare(temp1, temp0);
    // Compute z^8184 = z^4092^2 (loop 2 iterations of double squaring)
    for (loop_idx = 2; loop_idx < 10; loop_idx += 2) {
        fsquare(temp0, temp1);
        fsquare(temp1, temp0);
    }
    // Compute z^10230 = z^8184 * z^1023
    fmul(z_pow_20, temp1, z_pow_10);
    
    // Compute z^20460 = z^10230^2
    fsquare(temp0, z_pow_20);
    // Compute z^40920 = z^20460^2
    fsquare(temp1, temp0);
    // Compute z^81840 = z^40920^2 (loop 0x14/2 = 10 iterations of double squaring)
    for (loop_idx = 2; loop_idx < 0x14; loop_idx += 2) {
        fsquare(temp0, temp1);
        fsquare(temp1, temp0);
    }
    // Compute z^92070 = z^81840 * z^10230
    fmul(temp0, temp1, z_pow_20);
    
    // Compute z^184140 = z^92070^2
    fsquare(temp1, temp0);
    // Compute z^368280 = z^184140^2
    fsquare(temp0, temp1);
    // Compute z^736560 = z^368280^2 (loop 2 iterations of double squaring)
    for (loop_idx = 2; loop_idx < 10; loop_idx += 2) {
        fsquare(temp1, temp0);
        fsquare(temp0, temp1);
    }
    // Compute z^746790 = z^736560 * z^10230
    fmul(z_pow_50, temp0, z_pow_10);
    
    // Compute z^1493580 = z^746790^2
    fsquare(temp0, z_pow_50);
    // Compute z^2987160 = z^1493580^2
    fsquare(temp1, temp0);
    // Compute z^5974320 = z^2987160^2 (loop 0x32/2 = 25 iterations of double squaring)
    for (loop_idx = 2; loop_idx < 0x32; loop_idx += 2) {
        fsquare(temp0, temp1);
        fsquare(temp1, temp0);
    }
    // Compute z^6076620 = z^5974320 * z^10230
    fmul(z_pow_100, temp1, z_pow_50);
    
    // Compute z^12153240 = z^6076620^2
    fsquare(temp1, z_pow_100);
    // Compute z^24306480 = z^12153240^2
    fsquare(temp0, temp1);
    // Compute z^48612960 = z^24306480^2 (loop 100/2 = 50 iterations of double squaring)
    for (loop_idx = 2; loop_idx < 100; loop_idx += 2) {
        fsquare(temp1, temp0);
        fsquare(temp0, temp1);
    }
    // Compute z^49635990 = z^48612960 * z^10230
    fmul(temp1, temp0, z_pow_100);
    
    // Compute z^99271980 = z^49635990^2
    fsquare(temp0, temp1);
    // Compute z^198543960 = z^99271980^2
    fsquare(temp1, temp0);
    // Compute z^397087920 = z^198543960^2 (loop 0x32/2 = 25 iterations of double squaring)
    for (loop_idx = 2; loop_idx < 0x32; loop_idx += 2) {
        fsquare(temp0, temp1);
        fsquare(temp1, temp0);
    }
    // Compute z^407317950 = z^397087920 * z^10230
    fmul(temp0, temp1, z_pow_50);
    
    // Compute z^814635900 = z^407317950^2
    fsquare(temp1, temp0);
    // Compute z^1629271800 = z^814635900^2
    fsquare(temp0, temp1);
    // Compute z^3258543600 = z^1629271800^2
    fsquare(temp1, temp0);
    // Compute z^6517087200 = z^3258543600^2
    fsquare(temp0, temp1);
    // Compute z^13034174400 = z^6517087200^2
    fsquare(temp1, temp0);
    
    // Compute final result: z^(p-2) = z^13034174400 * z^11
    fmul(out, temp1, z_pow_11);
}