void cftf082(float *data) {
    // Twiddle factors for 8-point DFT
    // 0x200c: 0.70710678f
    // 0x2008: 0.70710678f
    // 0x2004: -0.70710678f
    float w1 = 0.70710678f;
    float w2 = 0.70710678f;
    float w3 = -0.70710678f;

    // Stage 1: 2-point DFTs (Butterflies)
    float a0 = data[0] - data[9];
    float a1 = data[1] + data[8];
    float a2 = data[0] + data[9];
    float a3 = data[1] - data[8];

    float a4 = data[4] - data[13];
    float a5 = data[5] + data[12];
    float b0 = w1 * (a4 - a5);
    float b1 = w1 * (a4 + a5);

    float a6 = data[4] + data[13];
    float a7 = data[5] - data[12];
    float b2 = w1 * (a6 - a7);
    float b3 = w1 * (a6 + a7);

    float a8 = data[2] - data[11];
    float a9 = data[3] + data[10];
    float c0 = w2 * a8 - w3 * a9;
    float c1 = w2 * a9 + w3 * a8;

    float a10 = data[2] + data[11];
    float a11 = data[3] - data[10];
    float c2 = w3 * a10 - w2 * a11;
    float c3 = w3 * a11 + w2 * a10;

    float a12 = data[6] - data[15];
    float a13 = data[7] + data[14];
    float c4 = w3 * a12 - w2 * a13;
    float c5 = w3 * a13 + w2 * a12;

    float a14 = data[6] + data[15];
    float a15 = data[7] - data[14];
    float c6 = w2 * a14 - w3 * a15;
    float c7 = w2 * a15 + w3 * a14;

    // Stage 2: 4-point DFTs combinations
    float d0 = a0 + b0;
    float d1 = a1 + b1;
    float d2 = c0 + c4;
    float d3 = c1 + c5;

    data[0] = d0 + d2;
    data[1] = d1 + d3;
    data[2] = d0 - d2;
    data[3] = d1 - d3;

    float d4 = a0 - b0;
    float d5 = a1 - b1;
    float d6 = c0 - c4;
    float d7 = c1 - c5;

    data[4] = d4 - d7;
    data[5] = d5 + d6;
    data[6] = d4 + d7;
    data[7] = d5 - d6;

    float d8 = a2 - b2;
    float d9 = a3 + b3;
    float d10 = c2 - c6;
    float d11 = c3 - c7;

    data[8] = d8 + d10;
    data[9] = d9 + d11;
    data[10] = d8 - d10;
    data[11] = d9 - d11;

    float d12 = a2 + b2;
    float d13 = a3 - b3;
    float d14 = c2 + c6;
    float d15 = c3 + c7;

    data[12] = d12 - d15;
    data[13] = d13 + d14;
    data[14] = d12 + d15;
    data[15] = d13 - d14;
}