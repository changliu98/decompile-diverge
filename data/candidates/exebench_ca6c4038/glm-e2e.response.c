void cftf161(cpx_t *a, cpx_t *w) {
    float w1r = w[1].real;
    float w1i = w[1].imag;
    float w2r = w[2].real;
    float w2i = w[2].imag;

    // Block 0
    float a0r = a[0].real + a[16].real;
    float a0i = a[0].imag + a[16].imag;
    float a1r = a[0].real - a[16].real;
    float a1i = a[0].imag - a[16].imag;
    float a2r = a[8].real + a[24].real;
    float a2i = a[8].imag + a[24].imag;
    float a3r = a[8].real - a[24].real;
    float a3i = a[8].imag - a[24].imag;

    float b0r = a0r + a2r;
    float b0i = a0i + a2i;
    float b1r = a0r - a2r;
    float b1i = a0i - a2i;
    float b2r = a1r - a3i;
    float b2i = a1i + a3r;
    float b3r = a1r + a3i;
    float b3i = a1i - a3r;

    // Block 1
    a0r = a[1].real + a[17].real;
    a0i = a[1].imag + a[17].imag;
    a1r = a[1].real - a[17].real;
    a1i = a[1].imag - a[17].imag;
    a2r = a[9].real + a[25].real;
    a2i = a[9].imag + a[25].imag;
    a3r = a[9].real - a[25].real;
    a3i = a[9].imag - a[25].imag;

    float c0r = a0r + a2r;
    float c0i = a0i + a2i;
    float c1r = a0r - a2r;
    float c1i = a0i - a2i;
    float c2r = a1r - a3i;
    float c2i = a1i + a3r;

    float d0r = w1r * c2r - w1i * c2i;
    float d0i = w1r * c2i + w1i * c2r;

    float c3r = a1r + a3i;
    float c3i = a1i - a3r;

    float d1r = w1r * c3r - w1i * c3i;
    float d1i = w1r * c3i + w1i * c3r;

    // Block 2
    a0r = a[2].real + a[18].real;
    a0i = a[2].imag + a[18].imag;
    a1r = a[2].real - a[18].real;
    a1i = a[2].imag - a[18].imag;
    a2r = a[10].real + a[26].real;
    a2i = a[10].imag + a[26].imag;
    a3r = a[10].real - a[26].real;
    a3i = a[10].imag - a[26].imag;

    float e0r = a0r + a2r;
    float e0i = a0i + a2i;
    float e1r = a0r - a2r;
    float e1i = a0i - a2i;
    float e2r = a1r - a3i;
    float e2i = a1i + a3r;

    float f0r = w2r * (e2r - e2i);
    float f0i = w2r * (e2i + e2r);

    float e3r = a1r + a3i;
    float e3i = a1i - a3r;

    float f1r = w2r * (e3r + e3i);
    float f1i = w2r * (e3i - e3r);

    // Block 3
    a0r = a[3].real + a[19].real;
    a0i = a[3].imag + a[19].imag;
    a1r = a[3].real - a[19].real;
    a1i = a[3].imag - a[19].imag;
    a2r = a[11].real + a[27].real;
    a2i = a[11].imag + a[27].imag;
    a3r = a[11].real - a[27].real;
    a3i = a[11].imag - a[27].imag;

    float g0r = a0r + a2r;
    float g0i = a0i + a2i;
    float g1r = a0r - a2r;
    float g1i = a0i - a2i;
    float g2r = a1r - a3i;
    float g2i = a1i + a3r;

    float h0r = w1i * g2r - w1r * g2i;
    float h0i = w1i * g2i + w1r * g2r;

    float g3r = a1r + a3i;
    float g3i = a1i - a3r;

    float h1r = w1i * g3r - w1r * g3i;
    float h1i = w1i * g3i + w1r * g3r;

    // Store Block 2
    a[12].real = b3r - f1r;
    a[12].imag = b3i - f1i;
    a[13].real = b3r + f1r;
    a[13].imag = b3i + f1i;
    a[14].real = b2r - h1r;
    a[14].imag = b2i - h1i;
    a[15].real = b2r + h1r;
    a[15].imag = b2i + h1i;

    // Store Block 1
    a[8].real  = b2r + d0r;
    a[8].imag  = b2i + d0i;
    a[9].real  = b2r - d0r;
    a[9].imag  = b2i - d0i;
    a[10].real = b3r - d1r;
    a[10].imag = b3i - d1i;
    a[11].real = b3r + d1r;
    a[11].imag = b3i + d1i;

    // Store Block 3
    float k0r = b1r - g1i;
    float k0i = b1i + g1r;
    float k1r = w2r * (k0r - k0i);
    float k1i = w2r * (k0i + k0r);
    float k2r = b1r + g1i;
    float k2i = b1i - g1r;
    float k3r = w2r * (k2r - k2i);
    float k3i = w2r * (k2i + k2r);

    float l0r = b1i - g1r;
    float l0i = b1r + g1i;
    float l1r = b1i + g1r;
    float l1i = b1r - g1i;

    a[4].real = l0r + k1r;
    a[4].imag = l0i + k1i;
    a[5].real = l0r - k1r;
    a[5].imag = l0i - k1i;
    a[6].real = l1r - k3r;
    a[6].imag = l1i - k3i;
    a[7].real = l1r + k3r;
    a[7].imag = l1i + k3i;

    // Store Block 0
    a[0].real = b0r + e0r;
    a[0].imag = b0i + e0i;
    a[1].real = b0r - e0r;
    a[1].imag = b0i - e0i;
    a[2].real = b1r - e1i;
    a[2].imag = b1i + e1r;
    a[3].real = b1r + e1i;
    a[3].imag = b1i - e1r;
}