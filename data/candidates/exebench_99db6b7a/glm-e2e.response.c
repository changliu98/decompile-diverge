void ifft4pt(float *data, float scale) {
    // Load the 4 complex numbers into local variables
    // data[0] = (a_r, a_i)
    float a_r = data[0];
    float a_i = data[1];
    
    // data[2] = (c_r, c_i)
    float c_r = data[4];
    float c_i = data[5];
    
    // data[1] = (b_r, b_i)
    float b_r = data[2];
    float b_i = data[3];
    
    // data[3] = (d_r, d_i)
    float d_r = data[6];
    float d_i = data[7];

    // Stage 1: 2-point DFTs
    // Butterfly for (a, c)
    float s1_r = a_r + c_r;
    float s1_i = a_i + c_i;
    c_r = a_r - c_r;
    c_i = a_i - c_i;

    // Butterfly for (b, d)
    float s2_r = b_r - d_r;
    float s2_i = b_i - d_i;
    b_r = b_r + d_r;
    b_i = b_i + d_i;

    // Stage 2: 4-point DFT combination
    // Butterfly for (s1, b)
    a_r = s1_r + b_r;
    a_i = s1_i + b_i;
    b_r = s1_r - b_r;
    b_i = s1_i - b_i;

    // Butterfly for (c, s2) with twiddle factor W_4^1 = -j
    // (c_r + j*c_i) * (-j) = c_i - j*c_r
    // Result = (c_r + j*c_i) + (c_i - j*c_r) = (c_r + c_i) + j*(c_i - c_r)
    d_r = c_r + s2_i;
    d_i = c_i - s2_r;
    c_r = c_r - s2_i;
    c_i = c_i + s2_r;

    // Apply the scaling factor and store the results back
    data[0] = a_r * scale;
    data[1] = a_i * scale;
    data[2] = b_r * scale;
    data[3] = b_i * scale;
    data[4] = c_r * scale;
    data[5] = c_i * scale;
    data[6] = d_r * scale;
    data[7] = d_i * scale;
}