void fft4pt(float *data) {
    // Load the 4 complex numbers (8 floats total)
    // data[0] = (ar, ai)
    float ar = data[0];
    float ai = data[1];
    // data[2] = (cr, ci)
    float cr = data[4];
    float ci = data[5];
    // data[1] = (br, bi)
    float br = data[2];
    float bi = data[3];
    // data[3] = (dr, di)
    float dr = data[6];
    float di = data[7];

    // Stage 1: Butterfly operations
    // Sum and difference of data[0] and data[2]
    float tpr = ar + cr;
    float tpi = ai + ci;
    float tmr = ar - cr;
    float tmi = ai - ci;

    // Sum and difference of data[1] and data[3]
    float tqr = br - dr;
    float tqi = bi + di;
    float trr = br + dr;
    float tri = bi - di;

    // Stage 2: Final combinations
    // data[0] = tpr + trr
    data[0] = tpr + trr;
    // data[1] = tpi + tri
    data[1] = tpi + tri;
    // data[2] = tmr - tqi
    data[2] = tmr - tqi;
    // data[3] = tmi + tqr
    data[3] = tmi + tqr;
    // data[4] = tpr - trr
    data[4] = tpr - trr;
    // data[5] = tpi - tri
    data[5] = tpi - tri;
    // data[6] = tmr + tqi
    data[6] = tmr + tqi;
    // data[7] = tmi - tqr
    data[7] = tmi - tqr;
}