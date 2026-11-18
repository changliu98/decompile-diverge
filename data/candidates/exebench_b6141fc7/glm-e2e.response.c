void R16SRFFT(float *in, float *out) {
    // Stage 1: 8-point DFT (Butterfly with distance 8)
    float t0  = in[0]  + in[8];
    float t1  = in[1]  + in[9];
    float t2  = in[2]  + in[10];
    float t3  = in[3]  + in[11];
    float t4  = in[4]  + in[12];
    float t5  = in[5]  + in[13];
    float t6  = in[6]  + in[14];
    float t7  = in[7]  + in[15];

    float t8  = in[0]  - in[8];
    float t9  = in[1]  - in[9];
    float t10 = in[2]  - in[10];
    float t11 = in[3]  - in[11];
    float t12 = in[12] - in[4];
    float t13 = in[13] - in[5];
    float t14 = in[14] - in[6];
    float t15 = in[15] - in[7];

    // Stage 2: 4-point DFTs
    // Twiddle factors are applied here (e.g., 0.7071067811865476 is sqrt(1/2))
    float tmp = (t13 - t9) * 0.7071067811865476;
    t9  = t9 * 0.7071067811865476 + tmp;
    t13 = t13 * -0.7071067811865476 + tmp;

    t14 = t14 * 0.7071067811865476;
    t10 = t10 * 0.7071067811865476;
    t14 = t14 - t10;
    t10 = t14 + t10 + t10;

    tmp = (t15 - t11) * 0.7071067811865476;
    t11 = t11 * 0.7071067811865476 + tmp;
    t15 = t15 * -0.7071067811865476 + tmp;

    t8  = t8  + t10;
    t10 = t8  - t10 - t10;
    t12 = t12 + t14;
    t14 = t12 - t14 - t14;
    t9  = t9  + t11;
    t11 = t9  - t11 - t11;
    t13 = t13 + t15;
    t15 = t13 - t15 - t15;

    // Stage 3: 2-point DFTs
    out[1]  = t8  + t9;
    out[7]  = t8  - t9;
    out[9]  = t12 + t13;
    out[15] = t13 - t12;
    out[5]  = t10 + t15;
    out[13] = t14 - t11;
    out[3]  = t10 - t15;
    out[11] = -t14 - t11;

    t0 = t0 + t4;
    t4 = t0 - t4 - t4;
    t1 = t1 + t5;
    t5 = t1 - t5 - t5;
    t6 = t6 + t2;
    t2 = t6 - t2 - t2;
    t7 = t7 + t3;
    t3 = t7 - t3 - t3;

    // Stage 4: Final combination
    out[0]  = t0 + t2;
    out[4]  = t0 - t2;
    
    t1 = t7 + t1;
    out[12] = t7 + t7 - t1;
    out[0]  = out[0] + t1;
    out[8]  = out[0] - t1 - t1;

    t5 = t5 * 0.7071067811865476;
    t3 = t3 * 0.7071067811865476;
    t5 = t5 - t3;
    t3 = t5 + t3 + t3;

    out[14] = t2 - t3;
    out[2]  = t5 + t4;
    out[6]  = t4 - t5;
    out[10] = -t3 - t2;
}